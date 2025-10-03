#ifndef STATUS_H
# define STATUS_H

# ifndef ERR
#  define ERR -1
# endif

# ifndef NO_ERR
#  define NO_ERR 0
# endif

# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef FAILURE
#  define FAILURE 1
# endif

# ifndef SYNTAX_ERR
#  define SYNTAX_ERR 2
# endif

# ifndef UNEXPECTED
#  define UNEXPECTED 3
# endif

# ifndef IS_DIR_ERR
#  define IS_DIR_ERR 126
# endif

# ifndef PERMISSION_ERR
#  define PERMISSION_ERR 126
# endif

# ifndef NOT_FOUND_ERR
#  define NOT_FOUND_ERR 127
# endif

# ifndef SYSTEMCALL_EXITSTATUS
#  define SYSTEMCALL_EXITSTATUS 255
# endif

# ifndef UNREACHABLE
#  define UNREACHABLE 1
# endif
#endif