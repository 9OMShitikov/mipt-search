add_library(DummyIndex ram.h ram.cpp)
target_link_libraries(DummyIndex Ranking)
add_catch(test_dummy
        index_ut.cpp
        ram.cpp
        ../net/context.h
        ../engine/ranking.h
        ../engine/ranking.cpp
        ../morphology/stemming.cpp
)