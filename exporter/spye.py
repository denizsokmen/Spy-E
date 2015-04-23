


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

        # return write_some_data(context, self.filepath, self.use_setting)
        if self.filepath == "":
            print("No suitable filename!")
            return {'FINISHED'}

        allMeshObjs = [obj for obj in bpy.context.scene.objects if obj.type == 'MESH'];

        entities = []
        with open(self.filepath, 'w', encoding='utf-8') as f:
            for obj in allMeshObjs:
                print(obj.name + " is at location" + str(obj.location))
                name = str(obj.name).lower()
                location = obj.location

                 # Special case for Cube.0001's
                if '.' in name:
                    name = name.split(".")[0] # becomes cube
                x = str(location.x)
                y = str(location.y)
                z = str(location.z)
                entity = ENTITIY_SCHEMA.format(str(obj.name),name,x,y,z)
                entities.append(entity)

            entitiesText = "\n".join(entities)
            world = WORLD_SCHEMA.format(entitiesText)
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
