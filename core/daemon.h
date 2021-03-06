// Copyright (c) 2015, Louis Opter <kalessin@kalessin.fr>
//
// This file is part of lighstd.
//
// lighstd is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// lighstd is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with lighstd.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#ifndef __attribute__
# define __atttribute__(e)
#endif

enum lgtd_verbosity;

enum { LGTD_DAEMON_TITLE_SIZE = 2048 };

enum { LGTD_DAEMON_ERRFMT_SIZE = 4096 };

bool lgtd_daemon_unleash(void); // \_o<
void lgtd_daemon_setup_proctitle(int, char *[], char *[]);
void lgtd_daemon_update_proctitle(void);
void lgtd_daemon_die_if_running_as_root_unless_requested(const char *);
void lgtd_daemon_set_user(const char *);
void lgtd_daemon_set_group(const char *);
bool lgtd_daemon_write_pidfile(const char *);
void lgtd_daemon_drop_privileges(void);
bool lgtd_daemon_makedirs(const char *);
uint32_t lgtd_daemon_randuint32(void);

int lgtd_daemon_syslog_facilitytoi(const char *);
void lgtd_daemon_syslog_open(const char *, enum lgtd_verbosity, int);
void lgtd_daemon_syslog_err(int, const char *, va_list) __attribute__((noreturn));
void lgtd_daemon_syslog_errx(int, const char *, va_list) __attribute__((noreturn));
void lgtd_daemon_syslog_warn(const char *, va_list);
void lgtd_daemon_syslog_warnx(const char *, va_list);
void lgtd_daemon_syslog_info(const char *, va_list);
void lgtd_daemon_syslog_debug(const char *, va_list);
