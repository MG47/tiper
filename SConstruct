#
# Tiper Text Editor Build File
#

PROJECT_ROOT_DIRECTORY = '.'

SOURCE_DIRECTORY = PROJECT_ROOT_DIRECTORY + '/source' 
BUILD_DIRECTORY = PROJECT_ROOT_DIRECTORY + '/build'

# Libs
TIPER_LIBS = 'ncurses'

# Source files
TIPER_SOURCES = Glob(SOURCE_DIRECTORY + '/*.c')

# Target binary
TIPER_BINARY = 'tiper'

TIPER_TARGET = BUILD_DIRECTORY + "/" + TIPER_BINARY

Program(source = TIPER_SOURCES, LIBS = TIPER_LIBS, target = TIPER_TARGET)

print(TIPER_SOURCES)
print(TIPER_LIBS)
print(TIPER_BINARY)


##TODO
#TIPER VERSION/REVISION - extract from tiper.h

