FIND_PROGRAM(
    GZIP_EXECUTABLE NAMES gzip
    DOC "Path to the gzip executable"
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Gzip DEFAULT_MSG GZIP_EXECUTABLE)
