CPPFLAGS = -MMD -MP
CXXFLAGS = -O2 -std=c++17 -Wall -Wextra
GTEST_DIR = googletest/googletest

.PHONY: all
all : bin/tests

.PHONY: clean veryclean
clean :
	rm -fr obj bin

veryclean : clean
	rm -fr obj-gtest

obj:
	mkdir -p obj

bin:
	mkdir -p bin

obj-gtest:
	mkdir -p obj-gtest

obj/tests:
	mkdir -p obj/tests

TEST_SOURCES = $(wildcard tests/*.cc)

-include $(TEST_SOURCES:%.cc=obj/%.d)

obj/tests/%.o: tests/%.cc | obj/tests
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Iinclude -I$(GTEST_DIR)/include -c $< -o $@

bin/tests: $(TEST_SOURCES:%.cc=obj/%.o) obj-gtest/gtest_main.a | bin
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -pthread -lpthread $^ -o $@

# Builds gtest.a and gtest_main.a.

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
obj-gtest/gtest-all.o : $(GTEST_SRCS_) | obj-gtest
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GTEST_DIR)/include $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc -o $@

obj-gtest/gtest_main.o : $(GTEST_SRCS_) | obj-gtest
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR)/include $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc -o $@

obj-gtest/gtest.a : obj-gtest/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

obj-gtest/gtest_main.a : obj-gtest/gtest-all.o obj-gtest/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
