/*
 *
 * Char_At.c
 *
 * Copyright 2019 Yuichi Yoshii
 *     吉井雄一 @ 吉井産業  you.65535.kir@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "Char_At.h"

int char_at_find(char, char *);

void char_at_set(Char_At * c, char * value) {
    c->arg = value;
    c->size = (int) strlen(value);
    c->start = 0;
    c->end = 0;
}

Char_At * char_at_without(Char_At * c, char target, char * exc) {
    for (int i = c->end; c->size > i; ++i) {
        if (target == c->arg[i]) {
            if (0 == c->start) {
                c->start = i;
            }
            c->end += i - c->end;
            return c;
        }
        else if (-1 < char_at_find(c->arg[i], exc)) {
            break;
        }
    }
    c->start = -1;
    c->end = -1;
    return c;
}

Char_At * char_at_within(Char_At * c, char target, char * inc) {
    for (int i = c->end; c->size > i; ++i) {
        if (target == c->arg[i]) {
            if (0 == c->start) {
                c->start = i;
            }
            c->end += i - c->end;
            return c;
        }
        else if (0 > char_at_find(c->arg[i], inc)) {
            break;
        }
    }
    c->start = -1;
    c->end = -1;
    return c;
}

Char_At * char_at_next(Char_At * c, char target) {
    for (int i = c->end; c->size > i; ++i) {
        if (target == c->arg[i]) {
            if (0 == c->start) {
                c->start = i;
            }
            c->end += i - c->end;
            return c;
        }
    }
    c->start = -1;
    c->end = -1;
    return c;
}

Char_At * char_at_tail(Char_At * c, char target) {
    for (int i = c->size; c->end < i; --i) {
        if (target == c->arg[i]) {
            if (0 == c->start) {
                c->start = i;
            }
            c->end = i;
            return c;
        }
    }
    c->end = c->size - 1;
    return c;
}

Char_At * char_at_skip(Char_At * c, int s) {
    c->end += s;
    return c;
}

int char_at_getStart(Char_At * c) {
    return c->start;
}

int char_at_getEnd(Char_At * c) {
    return c->end;
}

void char_at_dispose(Char_At * c) {
    errno = 0;
    free(c);
}

Char_At * Char_At_init(Char_At * c) {
    c->set = char_at_set;
    c->without = char_at_without;
    c->within = char_at_within;
    c->next = char_at_next;
    c->tail = char_at_tail;
    c->skip = char_at_skip;
    c->getStart = char_at_getStart;
    c->getEnd = char_at_getEnd;
    c->dispose = char_at_dispose;
    return c;
}

int char_at_find(char target, char * range) {
    int l = (int) strlen(range);
    for (int i = 0; l > i; ++i) {
        if (range[i] == target) {
            return i;
        }
    }
    return -1;
}