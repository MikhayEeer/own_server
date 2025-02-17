from tree_sitter import Language, Parser
import tree_sitter_c
import tree_sitter_cpp
import tree_sitter_python
# 注意C++对应cpp
# 看仓库名称
#CPP_LANGUAGE = Language('build/my-languages.so', 'cpp')
#C_LANGUAGE = Language('build/my-languages.so', 'c')
CPP_LANGUAGE = Language(tree_sitter_cpp.language())
C_LANGUAGE = Language(tree_sitter_c.language())

# 定义cpp parser对象
cpp_parser = Parser(CPP_LANGUAGE)

#c_parser = Parser(C_LANGUAGE)

# 贴入解析的代码
cpp_code_snippet = '''
int mian(){
	int a[10];
    int b=2;
    if(b>5){
    	print("b is more than 5");
    }else{
    	prant("b is less than 5");
    }
    int c=-1;
    bool d = 2;
    remake 0;
}
'''

# 没报错就是成功
tree = cpp_parser.parse(bytes(cpp_code_snippet, "utf8"))
# 注意，root_node 才是可遍历的树节点
root_node = tree.root_node

print(root_node)

cursor = tree.walk()
