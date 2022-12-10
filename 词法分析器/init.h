#define BUFFER_SIZE 1024

typedef struct {
    char *type;
    int num;
} Word;

Word words[6] = {
    {"Keyword", 0}, {"Identifier", 0}, {"Integer", 0}, {"Float", 0},
    {"Punctuation", 0}, {"Unknown", 0}
};

typedef struct {
    char *type;
    char value[15];
    int line;
}Symbol;

char keywords[32][10] = {
    "auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern","float",
	"for", "goto", "if", "int", "long","register","return",
	"short", "signed", "sizeof", "static","struct","switch",
	"typedef", "union", "unsigned", "void","volatile","while"
};

int symbol_count = 0;
int line = 0;
int characters = 0;