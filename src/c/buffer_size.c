/*
    pebble-unicode provides functions for handling Unicode on Pebble
    Copyright (C) 2016 Ben Caller

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <buffer_size.h>

// Correct snprintf size for strings which may contain unicode
size_t unicode_buffer_size(const char * s, size_t width) {
	size_t counter = 0;
	size_t updated_counter = 0;
	while(s[updated_counter] && updated_counter < width){
		counter = updated_counter;
		if((s[updated_counter] & 0xc0) == 0xc0) {
			// New multi-byte Unicode character
			uint8_t nbBytes = __builtin_clz(~s[updated_counter]);
			updated_counter += nbBytes;
		} else {
			// ASCII
			updated_counter++;
		}
	}
	// Append null character
	if(updated_counter < width)
		return updated_counter + 1;
	return counter + 1;
}
