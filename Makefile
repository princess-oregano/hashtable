SRCDIR := src
OBJDIR := obj

SRC := main.cpp list.cpp file.cpp hash_table.cpp
OBJ := obj/format.o $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
TARGET := hash_table

CXX := g++
CXXFLAGS := -O3 -g -std=c++14 -fmax-errors=100 -Wall -Wextra -mavx -mavx2     \
	    -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat           \
	    -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual            \
	    -Wchar-subscripts -Wconditionally-supported -Wconversion          \
	    -Wctor-dtor-privacy -Wempty-body -Wfloat-equal                    \
	    -Wformat-nonliteral -Wformat-security -Wformat-signedness         \
	    -Wformat=2 -Winline -Wlarger-than=40000 -Wlogical-op              \
	    -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd           \
	    -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls   \
	    -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192        \
	    -Wstrict-null-sentinel -Wstrict-overflow=2                        \
	    -Wsuggest-attribute=noreturn -Wsuggest-final-methods              \
	    -Wsuggest-final-types -Wsuggest-override -Wswitch-default         \
	    -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused     \
	    -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix              \
	    -Wno-missing-field-initializers -Wno-narrowing                    \
	    -Wno-old-style-cast -Wno-varargs -fcheck-new                      \
	    -fsized-deallocation -fstack-check -fstack-protector              \
	    -fstrict-overflow -flto-odr-type-merging                          \
	    -fno-omit-frame-pointer                                           \
	    -fsanitize=alignment                                              \
	    -fsanitize=address                                                \
	    -fsanitize=bool                                                   \
	    -fsanitize=bounds                                                 \
	    -fsanitize=enum                                                   \
	    -fsanitize=float-cast-overflow                                    \
	    -fsanitize=float-divide-by-zero                                   \
	    -fsanitize=integer-divide-by-zero                                 \
	    -fsanitize=leak                                                   \
	    -fsanitize=nonnull-attribute                                      \
	    -fsanitize=null                                                   \
	    -fsanitize=object-size                                            \
	    -fsanitize=return                                                 \
	    -fsanitize=returns-nonnull-attribute                              \
	    -fsanitize=shift                                                  \
	    -fsanitize=signed-integer-overflow                                \
	    -fsanitize=undefined                                              \
	    -fsanitize=unreachable                                            \
	    -fsanitize=vla-bound                                              \
	    -fsanitize=vptr                                                   \
	    -fPIE                                                             \
	    -lm -pie
.SILENT:
all: out run

run:
	printf "%s\n" "Running..."
	./$(TARGET)
	printf "%s\n" "Finished."

out: $(OBJDIR) $(OBJ)
	printf "%s\n" "Linking..."
	$(CXX) $(OBJ) -o $(TARGET) $(CXXFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	printf "%s\n" "Compiling $@..."
	$(CXX) -c $^ -o  $@ $(CXXFLAGS)

$(OBJDIR)/format.o: $(SRCDIR)/format.s
	printf "%s\n" "Assembling format.o..."
	nasm -g -f elf64 src/format.s -o obj/format.o

$(OBJDIR):
	printf "%s\n" "Making $@/ directory..."
	mkdir $@

clean:
	printf "%s\n" "Removing $(OBJDIR)/ directory..."
	rm -rf $(OBJDIR)
	printf "%s\n" "Done."

distclean:
	printf "%s\n" "Removing built files..."
	rm -rf $(OBJDIR)
	rm $(TARGET)
	printf "%s\n" "Done."


