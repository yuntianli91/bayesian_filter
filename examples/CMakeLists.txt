add_executable(ukf_demo ukf_demo.cc)
target_link_libraries(ukf_demo myFilter ${THIRD_PARTY_LIBS})