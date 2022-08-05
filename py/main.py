

typeTemplate = (
	('datetime', 'DateTimeDecorator', 'DATETIMEGDECORATOR_METHOD', 'ADD_DATETIME_DATAITEM'),
	('int', 'IntDecorator', 'INTGDECORATOR_METHOD', 'ADD_INT_DATAITEM'),
	('string', 'StringDecorator', 'STRINGDECORATOR_METHOD', 'ADD_STRING_DATAITEM'),
	('double', 'DoubleDecorator', 'DOUBLEGDECORATOR_METHOD', 'ADD_DOUBLE_DATAITEM'),
	('bool', 'BoolDecorator', 'BOOLGDECORATOR_METHOD', 'ADD_BOOL_DATAITEM'),
	('entity', 'Entity', '', 'ADD_CHILD'),
	('entity-list', 'EntityCollection', '', 'ADD_CHILD_ENTITYCOLLECTION'),
	('data-list', 'DataDecoratorCollection', '', 'ADD_CHILD_DATADECORATORCOLLECTION'),
	)

def getType(_type):
	for x in typeTemplate:
		if (x[0] == _type):
			return x[1]
	return ''

def getMethod(_type):
	for x in typeTemplate:
		if (x[0] == _type):
			return x[2]
	return ''	

def getAdd(_type):
	for x in typeTemplate:
		if (x[0] == _type):
			return x[3]
	return ''	


def create_template(className, includeList, methodList, propertyList, addpropertyList, toString):
	if toString.strip()=='':
		toString = 'QString()'

	with open("template.h","r", encoding="utf-8") as f:
		text = f.read()
		#print(text)
		text = text.replace('${DEFHEADER}', className.upper())
		text = text.replace('${INCLUDEENTITY}', includeList)
		text = text.replace('${CLASSNAME}', className)
		text = text.replace('${METHOD}', methodList)
		text = text.replace('${PROPERTY}', propertyList)
		print(text)

		name = '%s.h' % className
		with open(name, "w") as fh:
			fh.write(text)

	with open("template.cpp","r", encoding="utf-8") as f:
		text = f.read()
		#print(text)
		text = text.replace('${CLASSNAME}', className)
		text = text.replace('${ADDPROPERTY}', addpropertyList)
		text = text.replace('${TOSTRING}', toString)
		print(text)

		name = '%s.cpp' % className
		with open(name, "w") as fh:
			fh.write(text)

def read_property(filename):
	className = ''
	methodList = ''
	propertyList = ''
	addpropertyList = ''
	includeList = ''
	toString = ''
	with open(filename,"r") as f:
		lines = f.readlines()
		for i in range(0, len(lines)):
			line = lines[i].rstrip()
			print(line)
			lines2 = line.split(' ')
			print(lines2)

			if len(lines2) == 1 and lines2[0].strip()=='':
				print('============== %s' % includeList)
				toString = toString.rstrip(' + ", " +\n\t\t\t')
				if className.strip()!='':
					create_template(className, includeList, methodList, propertyList, addpropertyList, toString)
				className = ''
				methodList = ''
				propertyList = ''
				addpropertyList = ''
				includeList = ''
				toString = ''
				continue

			if len(lines2) == 1:
				className = lines2[0].rstrip()
				print(className)
				continue

			propertyType = getType(lines2[0])
			
			propertyClass = ''
			if (len(lines2) >= 3):
				propertyClass = lines2[2] 

			print('%s - %s' % (propertyType, propertyClass))
			if lines2[0] == 'entity':
				propertyType = propertyClass
			
				includeList += '#include "'
				includeList += propertyClass
				includeList += '.h"\n'

			elif lines2[0] == 'entity-list':
				propertyType += '<'
				propertyType += propertyClass
				propertyType += '>'

				includeList += '#include "'
				includeList += propertyClass
				includeList += '.h"\n'

			elif lines2[0] == 'data-list':
				propertyType += '<'
				propertyType += getType(propertyClass)
				propertyType += '>'
			else:
				methodList += getMethod(lines2[0])
				methodList += '('
				methodList += 'm_'
				methodList += lines2[1]
				methodList += ','
				methodList += 'set'
				methodList += lines2[1].title().replace('_', '')
				methodList += ','
				methodList += lines2[1]
				methodList += ')\n\t'

				addpropertyList += getAdd(lines2[0])
				addpropertyList += '("'
				addpropertyList += lines2[1]
				addpropertyList += '", QObject::tr("'
				addpropertyList += lines2[1]
				addpropertyList += '"))\n\t'

				#QString("%1=%2").arg(m_distance->label()).arg(m_distance->value()) + ", " +
				toString += 'QString("%1=%2").arg(m_'
				toString += lines2[1]
				toString += '->label()).arg(m_'
				toString += lines2[1]
				toString += '->value()) + ", " +\n\t\t\t'


			if lines2[0] == 'entity' or lines2[0] == 'entity-list' or lines2[0] == 'data-list':
				methodList += '\n\t'
				methodList += 'inline '
				methodList += propertyType
				methodList += ' *'
				methodList += lines2[1]
				methodList += '() const\n\t'
				methodList += '{ return '
				methodList += 'm_'
				methodList += lines2[1]
				methodList += '; }\n\t'

				addpropertyList += getAdd(lines2[0])
				addpropertyList += '('
				if lines2[0] == 'data-list':
					addpropertyList += getType(propertyClass)
				else:
					addpropertyList += propertyClass				
				addpropertyList += ', "'
				addpropertyList += lines2[1]
				addpropertyList += '")\n\t'

			propertyList += propertyType
			propertyList += ' *m_'
			propertyList += lines2[1]
			propertyList += ';\n\t'

read_property('property.txt')