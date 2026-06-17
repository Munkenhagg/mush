#ifndef MUSH_USER_CONFIG_H
#define MUSH_USER_CONFIG_H

#define ALWAYS_ECHO_COMMANDS // always echoes what is ran, even if -x isnt turned on. only echoes what is ran by the user, not scripts
#define MUSH_EXIT_MSG "Mush exited safely" // what is said when mush exists using the exit builtin
#define STRICT_MODE // adds strictness by exiting on errors
#define HISTORY_F ".mush_history" // defines the history file for mush, lives in $HOME (~)
#define HOME_LOCATION "/home" // should not be changed on most systems unless your home is elsewhere
#define ROOT_HOME_LOCATION "/root" // same as HOME_LOCATION, but for root(uid 0)
#define DUMP_DEBUG_INFO // dumps debug info at the start of main

#endif
