
import random

layerOne = []

for x in range(-10,10):
	column = []
	for y in range(-10,10):
		column.append(1)

	layerOne.append(column)


layerTwo = []

for x in range(-10,10):
	column = []
	
	for y in range(-10,10):
		box = 0
		if y == -10 or y == 9:
			box = 1
		if x == -10 or x == 9:
			box = 1

		column.append(box)

	layerTwo.append(column)




level = [layerOne, layerTwo, layerTwo]

level[2][5][3] = 1
level[2][5][4] = 1
level[2][5][5] = 1
level[2][5][5] = 1
level[2][5][5] = 1
level[2][5][5] = 1

name = "LevelOne"
version = "1.0"
extension = "xml"
fileName = "{0}-{1}.{2}".format(name,version,extension)

entitySchema = """
        <Entity name="box{0}">
            <Type>box</Type>
            <Position>
                <X>{1}</X>
                <Y>{2}</Y>
                <Z>{3}</Z>
            </Position>
            <Color>
                <R>{4}</R>
                <G>{5}</G>
                <B>{6}</B>
            </Color>
        </Entity>
"""

worldSchema = """
<World>
    <Name>"""+name+"""</Name>


    <Version>1.0</Version>
    <SkyBox>N/A</SkyBox>

    <Entities>
    	{0}
    </Entities>
</World>
"""

class Color:
	def __init__(self, r,g,b):
		self.r = r
		self.g = g
		self.b = b 

boxSize = 2
pos = (-10,0,-10)
def generateEntity(number, x,y,z, color=None):
	if color == None:
		r = str(random.randint(0,255)/255.0)
		g = str(random.randint(0,255)/255.0)
		b = str(random.randint(0,255)/255.0)
		color = Color(r,g,b)
	entity = entitySchema.format(number, \
								 pos[0]+x*boxSize, \
								 pos[1]+y*boxSize, \
								 pos[2]+z*boxSize, \
								 color.r, color.g, color.b)
	return entity

layerNumber = 0
entities = []

for layer in level:
	x = 0
	for row in layer:
		y = 0
		for column in row:
			if column == 1:
				entity = generateEntity(number=x+y, x=x, y=layerNumber, z=y, color=None)
				entities.append(entity)
			y += 1
		x += 1

	layerNumber += 1

entitiesText = "\n".join(entities)
world = worldSchema.format(entitiesText)

with open(fileName, "w") as f:
	f.write(world)




