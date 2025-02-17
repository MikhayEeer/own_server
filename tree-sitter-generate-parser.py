from tree_sitter import Language
Language.build_library(
    'build/c-cpp-parsers.so',
    [
        'vendor/tree-sitter-c',
        'vendor/tree-sitter-cpp'
    ]
)
