# Dungeon Project

## Week 7

### Run

```
./submit/Week07.exe
```

### CMakeLists.txt

```cmake
project(Week07_Framework)

set(Week07_SRC_LIST 
    ${PROJECT_SOURCE_DIR}/Week07/main.cpp
	
	${PROJECT_SOURCE_DIR}/Week07/main.h
	${PROJECT_SOURCE_DIR}/Week07/Hero.h
	${PROJECT_SOURCE_DIR}/Week07/Position.h
	${PROJECT_SOURCE_DIR}/Week07/Trigger.h
)

add_executable(Week07 ${Week07_SRC_LIST})
```

