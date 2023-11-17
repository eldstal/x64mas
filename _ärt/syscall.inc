
; First argument is syscall number
; Return value in rax
%macro syscall6 7

    ; Save argument registers
    ; just so our clobbering will be
    ; consistent
    push rdi
    push rsi
    push rdx
    push r10
    push r8
    push r9

    ; Push so that we don't risk
    ; clobbering an input register
    ; when setting up syscall args
    push %7
    push %6
    push %5
    push %4
    push %3
    push %2

    mov rax, %1
    mov rdi, [rsp+0]
    mov rsi, [rsp+0x8]
    mov rdx, [rsp+0x10]
    mov r10, [rsp+0x18]
    mov r8, [rsp+0x20]
    mov r9, [rsp+0x28]
    syscall

    ; Get rid of the inputs from the stack
    ; Not popping, because then we can't
    ; have non-register parameters
    add rsp, 0x30

    pop r9
    pop r8
    pop r10
    pop rdx
    pop rsi
    pop rdi
%endmacro


%macro syscall5 6
  syscall6 %1, %2, %3, %4, %5, %6, 0
%endmacro

%macro syscall4 5
  syscall6 %1, %2, %3, %4, %5, 0, 0
%endmacro

%macro syscall3 4
    ; Save argument registers
    ; just so our clobbering will be
    ; consistent
    push rdi
    push rsi
    push rdx

    ; Push so that we don't risk
    ; clobbering an input register
    ; when setting up syscall args
    push %4
    push %3
    push %2

    mov rax, %1
    mov rdi, [rsp+0]
    mov rsi, [rsp+0x8]
    mov rdx, [rsp+0x10]
    syscall

    ; Get rid of the inputs from the stack
    ; Not popping, because then we can't
    ; have non-register parameters
    add rsp, 0x18

    pop rdx
    pop rsi
    pop rdi
%endmacro

%macro syscall2 3
  syscall3 %1, %2, %3, 0
%endmacro

%macro syscall1 2
  syscall3 %1, %2, 0, 0
%endmacro




; 0x00
%define SYS_restart_syscall 0

; 0x01 | int error_code
%define SYS_exit 1

; 0x02
%define SYS_fork 2

; 0x03 | unsigned int fd | char *buf | size_t count
%define SYS_read 3

; 0x04 | unsigned int fd | const char *buf | size_t count
%define SYS_write 4

; 0x05 | const char *filename | int flags | umode_t mode
%define SYS_open 5

; 0x06 | unsigned int fd
%define SYS_close 6

; 0x07 | pid_t pid | int *stat_addr | int options
%define SYS_waitpid 7

; 0x08 | const char *pathname | umode_t mode
%define SYS_creat 8

; 0x09 | const char *oldname | const char *newname
%define SYS_link 9

; 0x0a | const char *pathname
%define SYS_unlink 10

; 0x0b | const char *name | const char *const *argv | const char *const *envp
%define SYS_execve 11

; 0x0c | const char *filename
%define SYS_chdir 12

; 0x0d | time_t *tloc
%define SYS_time 13

; 0x0e | const char *filename | umode_t mode | unsigned dev
%define SYS_mknod 14

; 0x0f | const char *filename | umode_t mode
%define SYS_chmod 15

; 0x10 | const char *filename | uid_t user | gid_t group
%define SYS_lchown 16

; - | - | - | - | - | - | - | Not implemented|
%define SYS_break 17

; 0x12 | const char *filename | struct __old_kernel_stat *statbuf
%define SYS_oldstat 18

; 0x13 | unsigned int fd | off_t offset | unsigned int origin
%define SYS_lseek 19

; 0x14
%define SYS_getpid 20

; 0x15 | char *dev_name | char *dir_name | char *type | unsigned long flags | void *data
%define SYS_mount 21

; 0x16 | char *name | int flags
%define SYS_umount 22

; 0x17 | uid_t uid
%define SYS_setuid 23

; 0x18
%define SYS_getuid 24

; 0x19 | time_t *tptr
%define SYS_stime 25

; 0x1a | long request | long pid | unsigned long addr | unsigned long data
%define SYS_ptrace 26

; 0x1b | unsigned int seconds
%define SYS_alarm 27

; 0x1c | unsigned int fd | struct __old_kernel_stat *statbuf
%define SYS_oldfstat 28

; 0x1d
%define SYS_pause 29

; 0x1e | char *filename | struct utimbuf *times
%define SYS_utime 30

; - | - | - | - | - | - | - | Not implemented|
%define SYS_stty 31

; - | - | - | - | - | - | - | Not implemented|
%define SYS_gtty 32

; 0x21 | const char *filename | int mode
%define SYS_access 33

; 0x22 | int increment
%define SYS_nice 34

; - | - | - | - | - | - | - | Not implemented|
%define SYS_ftime 35

; 0x24
%define SYS_sync 36

; 0x25 | pid_t pid | int sig
%define SYS_kill 37

; 0x26 | const char *oldname | const char *newname
%define SYS_rename 38

; 0x27 | const char *pathname | umode_t mode
%define SYS_mkdir 39

; 0x28 | const char *pathname
%define SYS_rmdir 40

; 0x29 | unsigned int fildes
%define SYS_dup 41

; 0x2a | int *fildes
%define SYS_pipe 42

; 0x2b | struct tms *tbuf
%define SYS_times 43

; - | - | - | - | - | - | - | Not implemented|
%define SYS_prof 44

; 0x2d | unsigned long brk
%define SYS_brk 45

; 0x2e | gid_t gid
%define SYS_setgid 46

; 0x2f
%define SYS_getgid 47

; 0x30 | int sig | __sighandler_t handler
%define SYS_signal 48

; 0x31
%define SYS_geteuid 49

; 0x32
%define SYS_getegid 50

; 0x33 | const char *name
%define SYS_acct 51

; 0x34 | char *name | int flags
%define SYS_umount2 52

; - | - | - | - | - | - | - | Not implemented|
%define SYS_lock 53

; 0x36 | unsigned int fd | unsigned int cmd | unsigned long arg
%define SYS_ioctl 54

; 0x37 | unsigned int fd | unsigned int cmd | unsigned long arg
%define SYS_fcntl 55

; - | - | - | - | - | - | - | Not implemented|
%define SYS_mpx 56

; 0x39 | pid_t pid | pid_t pgid
%define SYS_setpgid 57

; - | - | - | - | - | - | - | Not implemented|
%define SYS_ulimit 58

; 0x3b | struct oldold_utsname *name
%define SYS_oldolduname 59

; 0x3c | int mask
%define SYS_umask 60

; 0x3d | const char *filename
%define SYS_chroot 61

; 0x3e | unsigned dev | struct ustat *ubuf
%define SYS_ustat 62

; 0x3f | unsigned int oldfd | unsigned int newfd
%define SYS_dup2 63

; 0x40
%define SYS_getppid 64

; 0x41
%define SYS_getpgrp 65

; 0x42
%define SYS_setsid 66

; 0x43 | int sig | const struct old_sigaction *act | struct old_sigaction *oact
%define SYS_sigaction 67

; 0x44
%define SYS_sgetmask 68

; 0x45 | int newmask
%define SYS_ssetmask 69

; 0x46 | uid_t ruid | uid_t euid
%define SYS_setreuid 70

; 0x47 | gid_t rgid | gid_t egid
%define SYS_setregid 71

; 0x48 | int history0 | int history1 | old_sigset_t mask
%define SYS_sigsuspend 72

; 0x49 | old_sigset_t *set
%define SYS_sigpending 73

; 0x4a | char *name | int len
%define SYS_sethostname 74

; 0x4b | unsigned int resource | struct rlimit *rlim
%define SYS_setrlimit 75

; 0x4c | unsigned int resource | struct rlimit *rlim
%define SYS_getrlimit 76

; 0x4d | int who | struct rusage *ru
%define SYS_getrusage 77

; 0x4e | struct timeval *tv | struct timezone *tz
%define SYS_gettimeofday 78

; 0x4f | struct timeval *tv | struct timezone *tz
%define SYS_settimeofday 79

; 0x50 | int gidsetsize | gid_t *grouplist
%define SYS_getgroups 80

; 0x51 | int gidsetsize | gid_t *grouplist
%define SYS_setgroups 81

; 0x52 | int n | fd_set *inp | fd_set *outp | fd_set *exp | struct timeval *tvp
%define SYS_select 82

; 0x53 | const char *oldname | const char *newname
%define SYS_symlink 83

; 0x54 | const char *filename | struct __old_kernel_stat *statbuf
%define SYS_oldlstat 84

; 0x55 | const char *path | char *buf | int bufsiz
%define SYS_readlink 85

; 0x56 | const char *library
%define SYS_uselib 86

; 0x57 | const char *specialfile | int swap_flags
%define SYS_swapon 87

; 0x58 | int magic1 | int magic2 | unsigned int cmd | void *arg
%define SYS_reboot 88

; 0x59 | unsigned int fd | struct old_linux_dirent *dirent | unsigned int count
%define SYS_readdir 89

; 0x5a | unsigned long addr | unsigned long len | unsigned long prot | unsigned long flags | unsigned long fd | unsigned long off
%define SYS_mmap 90

; 0x5b | unsigned long addr | size_t len
%define SYS_munmap 91

; 0x5c | const char *path | long length
%define SYS_truncate 92

; 0x5d | unsigned int fd | unsigned long length
%define SYS_ftruncate 93

; 0x5e | unsigned int fd | umode_t mode
%define SYS_fchmod 94

; 0x5f | unsigned int fd | uid_t user | gid_t group
%define SYS_fchown 95

; 0x60 | int which | int who
%define SYS_getpriority 96

; 0x61 | int which | int who | int niceval
%define SYS_setpriority 97

; - | - | - | - | - | - | - | Not implemented|
%define SYS_profil 98

; 0x63 | const char *pathname | struct statfs *buf
%define SYS_statfs 99

; 0x64 | unsigned int fd | struct statfs *buf
%define SYS_fstatfs 100

; 0x65 | unsigned long from | unsigned long num | int turn_on
%define SYS_ioperm 101

; 0x66 | int call | unsigned long *args
%define SYS_socketcall 102

; 0x67 | int type | char *buf | int len
%define SYS_syslog 103

; 0x68 | int which | struct itimerval *value | struct itimerval *ovalue
%define SYS_setitimer 104

; 0x69 | int which | struct itimerval *value
%define SYS_getitimer 105

; 0x6a | const char *filename | struct __old_kernel_stat *statbuf
%define SYS_stat 106

; 0x6b | const char *filename | struct __old_kernel_stat *statbuf
%define SYS_lstat 107

; 0x6c | unsigned int fd | struct __old_kernel_stat *statbuf
%define SYS_fstat 108

; 0x6d | struct oldold_utsname *name
%define SYS_olduname 109

; 0x6e | unsigned int level
%define SYS_iopl 110

; 0x6f
%define SYS_vhangup 111

; - | - | - | - | - | - | - | Not implemented|
%define SYS_idle 112

; 0x71 | struct vm86_struct *v86
%define SYS_vm86old 113

; 0x72 | pid_t upid | int *stat_addr | int options | struct rusage *ru
%define SYS_wait4 114

; 0x73 | const char *specialfile
%define SYS_swapoff 115

; 0x74 | struct sysinfo *info
%define SYS_sysinfo 116

; 0x75 | unsigned int call | int first | unsigned long second | unsigned long third | void *ptr | long fifth
%define SYS_ipc 117

; 0x76 | unsigned int fd
%define SYS_fsync 118

; 0x77
%define SYS_sigreturn 119

; 0x78 | unsigned long clone_flags | unsigned long newsp | void *parent_tid | void *child_tid
%define SYS_clone 120

; 0x79 | char *name | int len
%define SYS_setdomainname 121

; 0x7a | struct old_utsname *name
%define SYS_uname 122

; 0x7b | int func | void *ptr | unsigned long bytecount
%define SYS_modify_ldt 123

; 0x7c | struct timex *txc_p
%define SYS_adjtimex 124

; 0x7d | unsigned long start | size_t len | unsigned long prot
%define SYS_mprotect 125

; 0x7e | int how | old_sigset_t *nset | old_sigset_t *oset
%define SYS_sigprocmask 126

; - | - | - | - | - | - | - | Not implemented|
%define SYS_create_module 127

; 0x80 | void *umod | unsigned long len | const char *uargs
%define SYS_init_module 128

; 0x81 | const char *name_user | unsigned int flags
%define SYS_delete_module 129

; - | - | - | - | - | - | - | Not implemented|
%define SYS_get_kernel_syms 130

; 0x83 | unsigned int cmd | const char *special | qid_t id | void *addr
%define SYS_quotactl 131

; 0x84 | pid_t pid
%define SYS_getpgid 132

; 0x85 | unsigned int fd
%define SYS_fchdir 133

; 0x86 | int func | long data
%define SYS_bdflush 134

; 0x87 | int option | unsigned long arg1 | unsigned long arg2
%define SYS_sysfs 135

; 0x88 | unsigned int personality
%define SYS_personality 136

; - | - | - | - | - | - | - | Not implemented|
%define SYS_afs_syscall 137

; 0x8a | uid_t uid
%define SYS_setfsuid 138

; 0x8b | gid_t gid
%define SYS_setfsgid 139

; 0x8c | unsigned int fd | unsigned long offset_high | unsigned long offset_low | loff_t *result | unsigned int origin
%define SYS__llseek 140

; 0x8d | unsigned int fd | struct linux_dirent *dirent | unsigned int count
%define SYS_getdents 141

; 0x8e | int n | fd_set *inp | fd_set *outp | fd_set *exp | struct timeval *tvp
%define SYS__newselect 142

; 0x8f | unsigned int fd | unsigned int cmd
%define SYS_flock 143

; 0x90 | unsigned long start | size_t len | int flags
%define SYS_msync 144

; 0x91 | unsigned long fd | const struct iovec *vec | unsigned long vlen
%define SYS_readv 145

; 0x92 | unsigned long fd | const struct iovec *vec | unsigned long vlen
%define SYS_writev 146

; 0x93 | pid_t pid
%define SYS_getsid 147

; 0x94 | unsigned int fd
%define SYS_fdatasync 148

; 0x95 | struct __sysctl_args *args
%define SYS__sysctl 149

; 0x96 | unsigned long start | size_t len
%define SYS_mlock 150

; 0x97 | unsigned long start | size_t len
%define SYS_munlock 151

; 0x98 | int flags
%define SYS_mlockall 152

; 0x99
%define SYS_munlockall 153

; 0x9a | pid_t pid | struct sched_param *param
%define SYS_sched_setparam 154

; 0x9b | pid_t pid | struct sched_param *param
%define SYS_sched_getparam 155

; 0x9c | pid_t pid | int policy | struct sched_param *param
%define SYS_sched_setscheduler 156

; 0x9d | pid_t pid
%define SYS_sched_getscheduler 157

; 0x9e
%define SYS_sched_yield 158

; 0x9f | int policy
%define SYS_sched_get_priority_max 159

; 0xa0 | int policy
%define SYS_sched_get_priority_min 160

; 0xa1 | pid_t pid | struct timespec *interval
%define SYS_sched_rr_get_interval 161

; 0xa2 | struct timespec *rqtp | struct timespec *rmtp
%define SYS_nanosleep 162

; 0xa3 | unsigned long addr | unsigned long old_len | unsigned long new_len | unsigned long flags | unsigned long new_addr
%define SYS_mremap 163

; 0xa4 | uid_t ruid | uid_t euid | uid_t suid
%define SYS_setresuid 164

; 0xa5 | uid_t *ruidp | uid_t *euidp | uid_t *suidp
%define SYS_getresuid 165

; 0xa6 | unsigned long cmd | unsigned long arg
%define SYS_vm86 166

; - | - | - | - | - | - | - | Not implemented|
%define SYS_query_module 167

; 0xa8 | struct pollfd *ufds | unsigned int nfds | int timeout_msecs
%define SYS_poll 168

; - | - | - | - | - | - | - | Not implemented|
%define SYS_nfsservctl 169

; 0xaa | gid_t rgid | gid_t egid | gid_t sgid
%define SYS_setresgid 170

; 0xab | gid_t *rgidp | gid_t *egidp | gid_t *sgidp
%define SYS_getresgid 171

; 0xac | int option | unsigned long arg2 | unsigned long arg3 | unsigned long arg4 | unsigned long arg5
%define SYS_prctl 172

; 0xad
%define SYS_rt_sigreturn 173

; 0xae | int sig | const struct sigaction *act | struct sigaction *oact | size_t sigsetsize
%define SYS_rt_sigaction 174

; 0xaf | int how | sigset_t *nset | sigset_t *oset | size_t sigsetsize
%define SYS_rt_sigprocmask 175

; 0xb0 | sigset_t *set | size_t sigsetsize
%define SYS_rt_sigpending 176

; 0xb1 | const sigset_t *uthese | siginfo_t *uinfo | const struct timespec *uts | size_t sigsetsize
%define SYS_rt_sigtimedwait 177

; 0xb2 | pid_t pid | int sig | siginfo_t *uinfo
%define SYS_rt_sigqueueinfo 178

; 0xb3 | sigset_t *unewset | size_t sigsetsize
%define SYS_rt_sigsuspend 179

; 0xb4 | char *buf size_t count | loff_t pos
%define SYS_pread64 180

; 0xb5 | const char *buf size_t count | loff_t pos
%define SYS_pwrite64 181

; 0xb6 | const char *filename | uid_t user | gid_t group
%define SYS_chown 182

; 0xb7 | char *buf | unsigned long size
%define SYS_getcwd 183

; 0xb8 | cap_user_header_t header | cap_user_data_t dataptr
%define SYS_capget 184

; 0xb9 | cap_user_header_t header | const cap_user_data_t data
%define SYS_capset 185

; 0xba | const stack_t *uss | stack_t *uoss
%define SYS_sigaltstack 186

; 0xbb | int out_fd | int in_fd | off_t *offset | size_t count
%define SYS_sendfile 187

; - | - | - | - | - | - | - | Not implemented|
%define SYS_getpmsg 188

; - | - | - | - | - | - | - | Not implemented|
%define SYS_putpmsg 189

; 0xbe
%define SYS_vfork 190

; 0xbf | unsigned int resource | struct rlimit *rlim
%define SYS_ugetrlimit 191

; 0xc0 | unsigned long addr | unsigned long len | unsigned long prot | unsigned long flags | unsigned long fd | unsigned long pgoff
%define SYS_mmap2 192

; 0xc1 | loff_t length
%define SYS_truncate64 193

; 0xc2 | loff_t length
%define SYS_ftruncate64 194

; 0xc3 | const char *filename | struct stat64 *statbuf
%define SYS_stat64 195

; 0xc4 | const char *filename | struct stat64 *statbuf
%define SYS_lstat64 196

; 0xc5 | unsigned long fd | struct stat64 *statbuf
%define SYS_fstat64 197

; 0xc6 | const char *filename | uid_t user | gid_t group
%define SYS_lchown32 198

; 0xc7
%define SYS_getuid32 199

; 0xc8
%define SYS_getgid32 200

; 0xc9
%define SYS_geteuid32 201

; 0xca
%define SYS_getegid32 202

; 0xcb | uid_t ruid | uid_t euid
%define SYS_setreuid32 203

; 0xcc | gid_t rgid | gid_t egid
%define SYS_setregid32 204

; 0xcd | int gidsetsize | gid_t *grouplist
%define SYS_getgroups32 205

; 0xce | int gidsetsize | gid_t *grouplist
%define SYS_setgroups32 206

; 0xcf | unsigned int fd | uid_t user | gid_t group
%define SYS_fchown32 207

; 0xd0 | uid_t ruid | uid_t euid | uid_t suid
%define SYS_setresuid32 208

; 0xd1 | uid_t *ruidp | uid_t *euidp | uid_t *suidp
%define SYS_getresuid32 209

; 0xd2 | gid_t rgid | gid_t egid | gid_t sgid
%define SYS_setresgid32 210

; 0xd3 | gid_t *rgidp | gid_t *egidp | gid_t *sgidp
%define SYS_getresgid32 211

; 0xd4 | const char *filename | uid_t user | gid_t group
%define SYS_chown32 212

; 0xd5 | uid_t uid
%define SYS_setuid32 213

; 0xd6 | gid_t gid
%define SYS_setgid32 214

; 0xd7 | uid_t uid
%define SYS_setfsuid32 215

; 0xd8 | gid_t gid
%define SYS_setfsgid32 216

; 0xd9 | const char *new_root | const char *put_old
%define SYS_pivot_root 217

; 0xda | unsigned long start | size_t len | unsigned char *vec
%define SYS_mincore 218

; 0xdb | unsigned long start | size_t len_in | int behavior
%define SYS_madvise 219

; 0xdc | unsigned int fd | struct linux_dirent64 *dirent | unsigned int count
%define SYS_getdents64 220

; 0xdd | unsigned int fd | unsigned int cmd | unsigned long arg
%define SYS_fcntl64 221

; 0xe0
%define SYS_gettid 224

; 0xe1 | loff_t offset size_t count
%define SYS_readahead 225

; 0xe2 | const char *pathname | const char *name | const void *value | size_t size | int flags
%define SYS_setxattr 226

; 0xe3 | const char *pathname | const char *name | const void *value | size_t size | int flags
%define SYS_lsetxattr 227

; 0xe4 | int fd | const char *name | const void *value | size_t size | int flags
%define SYS_fsetxattr 228

; 0xe5 | const char *pathname | const char *name | void *value | size_t size
%define SYS_getxattr 229

; 0xe6 | const char *pathname | const char *name | void *value | size_t size
%define SYS_lgetxattr 230

; 0xe7 | int fd | const char *name | void *value | size_t size
%define SYS_fgetxattr 231

; 0xe8 | const char *pathname | char *list | size_t size
%define SYS_listxattr 232

; 0xe9 | const char *pathname | char *list | size_t size
%define SYS_llistxattr 233

; 0xea | int fd | char *list | size_t size
%define SYS_flistxattr 234

; 0xeb | const char *pathname | const char *name
%define SYS_removexattr 235

; 0xec | const char *pathname | const char *name
%define SYS_lremovexattr 236

; 0xed | int fd | const char *name
%define SYS_fremovexattr 237

; 0xee | pid_t pid | int sig
%define SYS_tkill 238

; 0xef | int out_fd | int in_fd | loff_t *offset | size_t count
%define SYS_sendfile64 239

; 0xf0 | u32 *uaddr | int op | u32 val | struct timespec *utime | u32 *uaddr2 | u32 val3
%define SYS_futex 240

; 0xf1 | pid_t pid | unsigned int len | unsigned long *user_mask_ptr
%define SYS_sched_setaffinity 241

; 0xf2 | pid_t pid | unsigned int len | unsigned long *user_mask_ptr
%define SYS_sched_getaffinity 242

; 0xf3 | struct user_desc *u_info
%define SYS_set_thread_area 243

; 0xf4 | struct user_desc *u_info
%define SYS_get_thread_area 244

; 0xf5 | unsigned nr_events | aio_context_t *ctxp
%define SYS_io_setup 245

; 0xf6 | aio_context_t ctx
%define SYS_io_destroy 246

; 0xf7 | aio_context_t ctx_id | long min_nr | long nr | struct io_event *events | struct timespec *timeout
%define SYS_io_getevents 247

; 0xf8 | aio_context_t ctx_id | long nr | struct iocb * *iocbpp
%define SYS_io_submit 248

; 0xf9 | aio_context_t ctx_id | struct iocb *iocb | struct io_event *result
%define SYS_io_cancel 249

; 0xfa | loff_t offset size_t len | int advice
%define SYS_fadvise64 250

; 0xfc | int error_code
%define SYS_exit_group 252

; 0xfd | char *buf size_t len
%define SYS_lookup_dcookie 253

; 0xfe | int size
%define SYS_epoll_create 254

; 0xff | int epfd | int op | int fd | struct epoll_event *event
%define SYS_epoll_ctl 255

; 0x100 | int epfd | struct epoll_event *events | int maxevents | int timeout
%define SYS_epoll_wait 256

; 0x101 | unsigned long start | unsigned long size | unsigned long prot | unsigned long pgoff | unsigned long flags
%define SYS_remap_file_pages 257

; 0x102 | int *tidptr
%define SYS_set_tid_address 258

; 0x103 | const clockid_t which_clock | struct sigevent *timer_event_spec | timer_t *created_timer_id
%define SYS_timer_create 259

; 0x104 | timer_t timer_id | int flags | const struct itimerspec *new_setting | struct itimerspec *old_setting
%define SYS_timer_settime 260

; 0x105 | timer_t timer_id | struct itimerspec *setting
%define SYS_timer_gettime 261

; 0x106 | timer_t timer_id
%define SYS_timer_getoverrun 262

; 0x107 | timer_t timer_id
%define SYS_timer_delete 263

; 0x108 | const clockid_t which_clock | const struct timespec *tp
%define SYS_clock_settime 264

; 0x109 | const clockid_t which_clock | struct timespec *tp
%define SYS_clock_gettime 265

; 0x10a | const clockid_t which_clock | struct timespec *tp
%define SYS_clock_getres 266

; 0x10b | const clockid_t which_clock | int flags | const struct timespec *rqtp | struct timespec *rmtp
%define SYS_clock_nanosleep 267

; 0x10c | const char *pathname | size_t sz | struct statfs64 *buf
%define SYS_statfs64 268

; 0x10d | unsigned int fd | size_t sz | struct statfs64 *buf
%define SYS_fstatfs64 269

; 0x10e | pid_t tgid | pid_t pid | int sig
%define SYS_tgkill 270

; 0x10f | char *filename | struct timeval *utimes
%define SYS_utimes 271

; 0x110 | loff_t offset loff_t len | int advice
%define SYS_fadvise64_64 272

; - | - | - | - | - | - | - | Not implemented|
%define SYS_vserver 273

; 0x112 | unsigned long start | unsigned long len | unsigned long mode | unsigned long *nmask | unsigned long maxnode | unsigned flags
%define SYS_mbind 274

; 0x113 | int *policy | unsigned long *nmask | unsigned long maxnode | unsigned long addr | unsigned long flags
%define SYS_get_mempolicy 275

; 0x114 | int mode | unsigned long *nmask | unsigned long maxnode
%define SYS_set_mempolicy 276

; 0x115 | const char *u_name | int oflag | umode_t mode | struct mq_attr *u_attr
%define SYS_mq_open 277

; 0x116 | const char *u_name
%define SYS_mq_unlink 278

; 0x117 | mqd_t mqdes | const char *u_msg_ptr | size_t msg_len | unsigned int msg_prio | const struct timespec *u_abs_timeout
%define SYS_mq_timedsend 279

; 0x118 | mqd_t mqdes | char *u_msg_ptr | size_t msg_len | unsigned int *u_msg_prio | const struct timespec *u_abs_timeout
%define SYS_mq_timedreceive 280

; 0x119 | mqd_t mqdes | const struct sigevent *u_notification
%define SYS_mq_notify 281

; 0x11a | mqd_t mqdes | const struct mq_attr *u_mqstat | struct mq_attr *u_omqstat
%define SYS_mq_getsetattr 282

; 0x11b | unsigned long entry | unsigned long nr_segments | struct kexec_segment *segments | unsigned long flags
%define SYS_kexec_load 283

; 0x11c | int which | pid_t upid | struct siginfo *infop | int options | struct rusage *ru
%define SYS_waitid 284

; 0x11e | const char *_type | const char *_description | const void *_payload | size_t plen | key_serial_t ringid
%define SYS_add_key 286

; 0x11f | const char *_type | const char *_description | const char *_callout_info | key_serial_t destringid
%define SYS_request_key 287

; 0x120 | int option | unsigned long arg2 | unsigned long arg3 | unsigned long arg4 | unsigned long arg5
%define SYS_keyctl 288

; 0x121 | int which | int who | int ioprio
%define SYS_ioprio_set 289

; 0x122 | int which | int who
%define SYS_ioprio_get 290

; 0x123
%define SYS_inotify_init 291

; 0x124 | int fd | const char *pathname | u32 mask
%define SYS_inotify_add_watch 292

; 0x125 | int fd | __s32 wd
%define SYS_inotify_rm_watch 293

; 0x126 | pid_t pid | unsigned long maxnode | const unsigned long *old_nodes | const unsigned long *new_nodes
%define SYS_migrate_pages 294

; 0x127 | int dfd | const char *filename | int flags | umode_t mode
%define SYS_openat 295

; 0x128 | int dfd | const char *pathname | umode_t mode
%define SYS_mkdirat 296

; 0x129 | int dfd | const char *filename | umode_t mode | unsigned dev
%define SYS_mknodat 297

; 0x12a | int dfd | const char *filename | uid_t user | gid_t group | int flag
%define SYS_fchownat 298

; 0x12b | int dfd | const char *filename | struct timeval *utimes
%define SYS_futimesat 299

; 0x12c | int dfd | const char *filename | struct stat64 *statbuf | int flag
%define SYS_fstatat64 300

; 0x12d | int dfd | const char *pathname | int flag
%define SYS_unlinkat 301

; 0x12e | int olddfd | const char *oldname | int newdfd | const char *newname
%define SYS_renameat 302

; 0x12f | int olddfd | const char *oldname | int newdfd | const char *newname | int flags
%define SYS_linkat 303

; 0x130 | const char *oldname | int newdfd | const char *newname
%define SYS_symlinkat 304

; 0x131 | int dfd | const char *pathname | char *buf | int bufsiz
%define SYS_readlinkat 305

; 0x132 | int dfd | const char *filename | umode_t mode
%define SYS_fchmodat 306

; 0x133 | int dfd | const char *filename | int mode
%define SYS_faccessat 307

; 0x134 | int n | fd_set *inp | fd_set *outp | fd_set *exp | struct timespec *tsp | void *sig
%define SYS_pselect6 308

; 0x135 | struct pollfd *ufds | unsigned int nfds | struct timespec *tsp | const sigset_t *sigmask | size_t sigsetsize
%define SYS_ppoll 309

; 0x136 | unsigned long unshare_flags
%define SYS_unshare 310

; 0x137 | struct robust_list_head *head | size_t len
%define SYS_set_robust_list 311

; 0x138 | int pid | struct robust_list_head * *head_ptr | size_t *len_ptr
%define SYS_get_robust_list 312

; 0x139 | int fd_in | loff_t *off_in | int fd_out | loff_t *off_out | size_t len | unsigned int flags
%define SYS_splice 313

; 0x13a | loff_t offset loff_t nbytes | unsigned int flags
%define SYS_sync_file_range 314

; 0x13b | int fdin | int fdout | size_t len | unsigned int flags
%define SYS_tee 315

; 0x13c | int fd | const struct iovec *iov | unsigned long nr_segs | unsigned int flags
%define SYS_vmsplice 316

; 0x13d | pid_t pid | unsigned long nr_pages | const void * *pages | const int *nodes | int *status | int flags
%define SYS_move_pages 317

; 0x13e | unsigned *cpup | unsigned *nodep | struct getcpu_cache *unused
%define SYS_getcpu 318

; 0x13f | int epfd | struct epoll_event *events | int maxevents | int timeout | const sigset_t *sigmask | size_t sigsetsize
%define SYS_epoll_pwait 319

; 0x140 | int dfd | const char *filename | struct timespec *utimes | int flags
%define SYS_utimensat 320

; 0x141 | int ufd | sigset_t *user_mask | size_t sizemask
%define SYS_signalfd 321

; 0x142 | int clockid | int flags
%define SYS_timerfd_create 322

; 0x143 | unsigned int count
%define SYS_eventfd 323

; 0x144 | int mode loff_t offset | loff_t len
%define SYS_fallocate 324

; 0x145 | int ufd | int flags | const struct itimerspec *utmr | struct itimerspec *otmr
%define SYS_timerfd_settime 325

; 0x146 | int ufd | struct itimerspec *otmr
%define SYS_timerfd_gettime 326

; 0x147 | int ufd | sigset_t *user_mask | size_t sizemask | int flags
%define SYS_signalfd4 327

; 0x148 | unsigned int count | int flags
%define SYS_eventfd2 328

; 0x149 | int flags
%define SYS_epoll_create1 329

; 0x14a | unsigned int oldfd | unsigned int newfd | int flags
%define SYS_dup3 330

; 0x14b | int *fildes | int flags
%define SYS_pipe2 331

; 0x14c | int flags
%define SYS_inotify_init1 332

; 0x14d | unsigned long fd | const struct iovec *vec | unsigned long vlen | unsigned long pos_l | unsigned long pos_h
%define SYS_preadv 333

; 0x14e | unsigned long fd | const struct iovec *vec | unsigned long vlen | unsigned long pos_l | unsigned long pos_h
%define SYS_pwritev 334

; 0x14f | pid_t tgid | pid_t pid | int sig | siginfo_t *uinfo
%define SYS_rt_tgsigqueueinfo 335

; 0x150 | struct perf_event_attr *attr_uptr | pid_t pid | int cpu | int group_fd | unsigned long flags
%define SYS_perf_event_open 336

; 0x151 | int fd | struct mmsghdr *mmsg | unsigned int vlen | unsigned int flags | struct timespec *timeout
%define SYS_recvmmsg 337

; 0x152 | unsigned int flags | unsigned int event_f_flags
%define SYS_fanotify_init 338

; 0x153 | unsigned int flags __u64 mask | int dfd const char *pathname
%define SYS_fanotify_mark 339

; 0x154 | pid_t pid | unsigned int resource | const struct rlimit64 *new_rlim | struct rlimit64 *old_rlim
%define SYS_prlimit64 340

; 0x155 | int dfd | const char *name | struct file_handle *handle | int *mnt_id | int flag
%define SYS_name_to_handle_at 341

; 0x156 | int mountdirfd | struct file_handle *handle | int flags
%define SYS_open_by_handle_at 342

; 0x157 | const clockid_t which_clock | struct timex *utx
%define SYS_clock_adjtime 343

; 0x158 | int fd
%define SYS_syncfs 344

; 0x159 | int fd | struct mmsghdr *mmsg | unsigned int vlen | unsigned int flags
%define SYS_sendmmsg 345

; 0x15a | int fd | int nstype
%define SYS_setns 346

; 0x15b | pid_t pid | const struct iovec *lvec | unsigned long liovcnt | const struct iovec *rvec | unsigned long riovcnt | unsigned long flags
%define SYS_process_vm_readv 347

; 0x15c | pid_t pid | const struct iovec *lvec | unsigned long liovcnt | const struct iovec *rvec | unsigned long riovcnt | unsigned long flags
%define SYS_process_vm_writev 348

; 0x15d | pid_t pid1 | pid_t pid2 | int type | unsigned long idx1 | unsigned long idx2
%define SYS_kcmp 349




