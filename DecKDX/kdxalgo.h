/*

KDX encryption/decryption algorithm 0.1
by Luigi Auriemma
e-mail: aluigi@autistici.org
web:    aluigi.org

------------
INTRODUCTION
------------
The following is the algorithm used by KDX (http://www.haxialsoftware.com)
for encrypting and decrypting its data.

In general each KDX packet is composed by:

  4  bytes: key
  32 bytes: header
  ?? bytes: data

my function returns the new key value which is needed for the subsequent
dec/encryption of the data block.
remember that each value in the packet (key included) is in big endian
and the size of the data is ever padded to 4 bytes.
The protocol is not very easily to handle, in any case my research covers
only this algorithm.

-------
LICENSE
-------
    Copyright 2007 Luigi Auriemma

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

    http://www.gnu.org/licenses/gpl.txt
*/

#include <stdlib.h>
#include <stdint.h>
#include <winsock.h>
// #include <netinet/in.h> incl in autobuild script



uint32_t kdx_crypt(uint32_t key, uint8_t *data, unsigned datalen) {
    uint32_t    *data32;
    unsigned    i;

    datalen >>= 2;
    data32 = (uint32_t *)data;

    for(i = 0; i < datalen; i++) {
        key = (key << 1) + 0x4878;
        data32[i] ^= ntohl(key);
    }

    return(key);
}


