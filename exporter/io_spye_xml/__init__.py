#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software Foundation,
#  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
import shutil


bl_info = {
    "name": "Spy-E World Exporter",
    "author": "Spy-E Team",
    "version": (1,0,0),
    "blender": (2, 7, 4),
    "location": "File > Export > Spy-E World (.xml)",
    "description": "Export as Spy-E World (.xml)",
    "warning": "",
    "wiki_url": "https://github.com/denizsokmen/Spy-E",
    "tracker_url": "https://github.com/denizsokmen/Spy-E/issues",
    "category": "Import-Export"}


import bpy
import os


ENTITIY_SCHEMA = """
        <Entity name="{0}">
            <Type>{1}</Type>
            <Position>
                <X>{2}</X>
                <Y>{3}</Y>
                <Z>{4}</Z>
            </Position>
        </Entity>
"""

WORLD_SCHEMA = """
<World>
    <Entities>
        {0}
    </Entities>
</World>
"""

if "bpy" in locals():
    import importlib
    if "export_obj" in locals():
        importlib.reload(export_obj)



# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator


class ExportSpyWorld(Operator, ExportHelper):
    """This appears in the tooltip of the operator and in the generated docs"""
    bl_idname = "export_test.xml"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "Export as Spy-E World (.xml)"

    # ExportHelper mixin class uses this
    filename_ext = ".xml"

    filter_glob = StringProperty(
            default="*.xml",
            options={'HIDDEN'},
            )

    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.
    use_setting = BoolProperty(
            name="Example Boolean",
            description="Example Tooltip",
            default=True,
            )

    type = EnumProperty(
            name="Example Enum",
            description="Choose between two items",
            items=(('OPT_A', "First Option", "Description one"),
                   ('OPT_B', "Second Option", "Description two")),
            default='OPT_A',
            )

    def execute(self, context):
        from . import export_obj

        # return write_some_data(context, self.filepath, self.use_setting)
        if self.filepath == "":
            print("No suitable filename!")
            return {'FINISHED'}

        allMeshObjs = [obj for obj in bpy.context.scene.objects if obj.type == 'MESH'];

        entities = []

        filepath, filename = os.path.split(self.filepath)
        (shortname, extension) = os.path.splitext(filename)

        directoryPath = os.path.join(filepath, shortname)
        entitiesDirectoryPath = os.path.join(directoryPath, "entities")

        if not os.path.exists(directoryPath):  # FIXME: may have race condition
            os.makedirs(directoryPath)
            os.makedirs(entitiesDirectoryPath)
        else:
            shutil.rmtree(directoryPath)
            os.makedirs(directoryPath)
            os.makedirs(entitiesDirectoryPath)


        spyWorldPath = os.path.join(directoryPath, filename)


        entity_set = set()

        for obj in allMeshObjs:
            print(obj.name + " is at location" + str(obj.location))
            name = str(obj.name).lower()
            location = obj.location

             # Special case for Cube.0001's
            if '.' in name:
                name = name.split(".")[0] # becomes cube
            x = str(location.x)
            y = str(-location.y)
            z = str(location.z)
            entity = ENTITIY_SCHEMA.format(str(obj.name),name,x,z,y) # Spy-E's Up is +Y, Blender's is +Z
            entities.append(entity)
            if name not in entity_set:
                entity_set.add(name)
                entity_own_folder = os.path.join(entitiesDirectoryPath, name)
                os.makedirs(entity_own_folder)
                entity_full_path = os.path.join(entity_own_folder, name) + ".obj"
                export_obj.write_file(entity_full_path, [obj], context.scene, EXPORT_NORMALS=True, EXPORT_TRI=True,EXPORT_APPLY_MODIFIERS=True, EXPORT_EDGES=True, EXPORT_BLEN_OBS=True)

        entitiesText = "\n".join(entities)
        world = WORLD_SCHEMA.format(entitiesText)

        with open(spyWorldPath, 'w', encoding='utf-8') as f:

            f.write(world)


        return {'FINISHED'}



# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ExportSpyWorld.bl_idname, text="Spy-E World (.xml)")


def register():
    bpy.utils.register_class(ExportSpyWorld)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportSpyWorld)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()

    # test call
    bpy.ops.export_test.some_data('INVOKE_DEFAULT')
