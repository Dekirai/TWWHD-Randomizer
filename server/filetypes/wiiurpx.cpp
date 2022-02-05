// Copyright (C) 2016  CBH <maodatouint8_t8@163.com>
// Licensed under the terms of the GNU GPL, version 3
// http://www.gnu.org/licenses/gpl-3.0.txt

//Largely pulled from https://github.com/0CBH0/wiiurpxtool
//Several things are changed to be consistent with other filetypes

#include "wiiurpx.hpp"

#include <zlib.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>

#include "../utility/byteswap.hpp"



static uint32_t pos;


uint32_t crc32_rpx(uint32_t crc, uint8_t* buff, uint32_t len)
{
    uint32_t crc_table[256];
    for (uint32_t i = 0; i < 256; i++)
    {
        uint32_t c = i;
        for (uint32_t j = 0; j < 8; j++)
        {
            if (c & 1)
                c = 0xedb88320L ^ (c >> 1);
            else
                c = c >> 1;
        }
        crc_table[i] = c;
    }
    crc = ~crc;
    for (uint32_t i = 0; i < len; i++)
        crc = (crc >> 8) ^ crc_table[(crc ^ buff[i]) & 0xff];
    return ~crc;
}

bool SortFunc(const Elf32_Shdr_Sort& v1, const Elf32_Shdr_Sort& v2)
{
    return v1.sh_offset < v2.sh_offset;
}


namespace FileTypes {
    const char* RPXErrorGetName(RPXError err) {
        switch (err) {
            case RPXError::NONE:
                return "NONE";
            case RPXError::COULD_NOT_OPEN:
                return "COULD_NOT_OPEN";
            case RPXError::NOT_RPX:
                return "NOT_RPX";
            case RPXError::UNKNOWN_E_TYPE:
                return "UNKNOWN_E_TYPE";
            case RPXError::ZLIB_ERROR:
                return "ZLIB_ERROR";
            case RPXError::REACHED_EOF:
                return "REACHED_EOF";
            default:
                return "UNKNOWN";
        }
    }

    RPXError rpx_decompress(std::istream& in, std::ostream& out)
    {
        Elf32_Ehdr ehdr;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_ident[0]), 0x10)) return RPXError::REACHED_EOF;
        if (std::strncmp(reinterpret_cast<char*>(&ehdr.e_ident[0]), "\x7F""ELF", 4)) return RPXError::NOT_RPX;

        if (!in.read(reinterpret_cast<char*>(&ehdr.e_type), sizeof(ehdr.e_type))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_machine), sizeof(ehdr.e_machine))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_version), sizeof(ehdr.e_version))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_entry), sizeof(ehdr.e_entry))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_phoff), sizeof(ehdr.e_phoff))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_shoff), sizeof(ehdr.e_shoff))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_flags), sizeof(ehdr.e_flags))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_ehsize), sizeof(ehdr.e_ehsize))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_phentsize), sizeof(ehdr.e_phentsize))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_phnum), sizeof(ehdr.e_phnum))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_shentsize), sizeof(ehdr.e_shentsize))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_shnum), sizeof(ehdr.e_shnum))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_shstrndx), sizeof(ehdr.e_shstrndx))) return RPXError::REACHED_EOF;

        Utility::byteswap_inplace(ehdr.e_type);
        Utility::byteswap_inplace(ehdr.e_machine);
        Utility::byteswap_inplace(ehdr.e_version);
        Utility::byteswap_inplace(ehdr.e_entry);
        Utility::byteswap_inplace(ehdr.e_phoff);
        Utility::byteswap_inplace(ehdr.e_shoff);
        Utility::byteswap_inplace(ehdr.e_flags);
        Utility::byteswap_inplace(ehdr.e_ehsize);
        Utility::byteswap_inplace(ehdr.e_phentsize);
        Utility::byteswap_inplace(ehdr.e_phnum);
        Utility::byteswap_inplace(ehdr.e_shentsize);
        Utility::byteswap_inplace(ehdr.e_shnum);
        Utility::byteswap_inplace(ehdr.e_shstrndx);
        
        if (ehdr.e_type != 0xFE01) return RPXError::UNKNOWN_E_TYPE;

        uint32_t shdr_data_elf_offset = ehdr.e_shoff + ehdr.e_shnum * ehdr.e_shentsize;
        out.write(reinterpret_cast<char*>(&ehdr.e_ident[0]), 0x10);

        auto e_type = Utility::byteswap(ehdr.e_type);
        auto e_machine = Utility::byteswap(ehdr.e_machine);
        auto e_version = Utility::byteswap(ehdr.e_version);
        auto e_entry = Utility::byteswap(ehdr.e_entry);
        auto e_phoff = Utility::byteswap(ehdr.e_phoff);
        auto e_shoff = Utility::byteswap(ehdr.e_shoff);
        auto e_flags = Utility::byteswap(ehdr.e_flags);
        auto e_ehsize = Utility::byteswap(ehdr.e_ehsize);
        auto e_phentsize = Utility::byteswap(ehdr.e_phentsize);
        auto e_phnum = Utility::byteswap(ehdr.e_phnum);
        auto e_shentsize = Utility::byteswap(ehdr.e_shentsize);
        auto e_shnum = Utility::byteswap(ehdr.e_shnum);
        auto e_shstrndx = Utility::byteswap(ehdr.e_shstrndx);

        out.write(reinterpret_cast<char*>(&e_type), sizeof(e_type));
        out.write(reinterpret_cast<char*>(&e_machine), sizeof(e_machine));
        out.write(reinterpret_cast<char*>(&e_version), sizeof(e_version));
        out.write(reinterpret_cast<char*>(&e_entry), sizeof(e_entry));
        out.write(reinterpret_cast<char*>(&e_phoff), sizeof(e_phoff));
        out.write(reinterpret_cast<char*>(&e_shoff), sizeof(e_shoff));
        out.write(reinterpret_cast<char*>(&e_flags), sizeof(e_flags));
        out.write(reinterpret_cast<char*>(&e_ehsize), sizeof(e_ehsize));
        out.write(reinterpret_cast<char*>(&e_phentsize), sizeof(e_phentsize));
        out.write(reinterpret_cast<char*>(&e_phnum), sizeof(e_phnum));
        out.write(reinterpret_cast<char*>(&e_shentsize), sizeof(e_shentsize));
        out.write(reinterpret_cast<char*>(&e_shnum), sizeof(e_shnum));
        out.write(reinterpret_cast<char*>(&e_shstrndx), sizeof(e_shstrndx));
        uint32_t crc_data_offset = 0;
        uint32_t *crcs = new uint32_t[ehdr.e_shnum];
        std::vector<Elf32_Shdr_Sort> shdr_table_index;
        Elf32_Shdr *shdr_table = new Elf32_Shdr[ehdr.e_shnum];
        while (static_cast<uint32_t>(out.tellp()) < shdr_data_elf_offset) out.put(0);
        if (!in.seekg(ehdr.e_shoff)) return RPXError::REACHED_EOF;
        for (uint32_t i = 0; i < ehdr.e_shnum; i++)
        {
            crcs[i] = 0;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_name), sizeof(shdr_table[i].sh_name))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_type), sizeof(shdr_table[i].sh_type))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_flags), sizeof(shdr_table[i].sh_flags))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_addr), sizeof(shdr_table[i].sh_addr))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_offset), sizeof(shdr_table[i].sh_offset))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_size), sizeof(shdr_table[i].sh_size))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_link), sizeof(shdr_table[i].sh_link))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_info), sizeof(shdr_table[i].sh_info))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_addralign), sizeof(shdr_table[i].sh_addralign))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_entsize), sizeof(shdr_table[i].sh_entsize))) return RPXError::REACHED_EOF;

            Utility::byteswap_inplace(shdr_table[i].sh_name);
            shdr_table[i].sh_type = static_cast<SectionType>(Utility::byteswap(static_cast<std::underlying_type_t<SectionType>>(shdr_table[i].sh_type)));
            Utility::byteswap_inplace(shdr_table[i].sh_flags);
            Utility::byteswap_inplace(shdr_table[i].sh_addr);
            Utility::byteswap_inplace(shdr_table[i].sh_offset);
            Utility::byteswap_inplace(shdr_table[i].sh_size);
            Utility::byteswap_inplace(shdr_table[i].sh_link);
            Utility::byteswap_inplace(shdr_table[i].sh_info);
            Utility::byteswap_inplace(shdr_table[i].sh_addralign);
            Utility::byteswap_inplace(shdr_table[i].sh_entsize);

            if (shdr_table[i].sh_offset != 0)
            {
                Elf32_Shdr_Sort shdr_index;
                shdr_index.index = i;
                shdr_index.sh_offset = shdr_table[i].sh_offset;
                shdr_table_index.push_back(shdr_index);
            }
        }
        std::sort(shdr_table_index.begin(), shdr_table_index.end(), SortFunc);
        for(std::vector<Elf32_Shdr_Sort>::iterator shdr_index=shdr_table_index.begin();shdr_index!=shdr_table_index.end();shdr_index++)
        {
            pos = shdr_table[shdr_index->index].sh_offset;
            if (!in.seekg(pos))
            {
                return RPXError::REACHED_EOF;
            }
            shdr_table[shdr_index->index].sh_offset = out.tellp();
            if((shdr_table[shdr_index->index].sh_flags & SHF_RPL_ZLIB) == SHF_RPL_ZLIB)
            {
                uint32_t data_size = shdr_table[shdr_index->index].sh_size-4;

                if (!in.read(reinterpret_cast<char*>(&shdr_table[shdr_index->index].sh_size), sizeof(shdr_table[shdr_index->index].sh_size))) return RPXError::REACHED_EOF;
                Utility::byteswap_inplace(shdr_table[shdr_index->index].sh_size);

                uint32_t block_size = CHUNK;
                uint32_t have;
                z_stream strm;
                char buff_in[CHUNK];
                char buff_out[CHUNK];
                strm.zalloc = Z_NULL;
                strm.zfree = Z_NULL;
                strm.opaque = Z_NULL;
                strm.avail_in = 0;
                strm.next_in = Z_NULL;
                int err = Z_OK;
                if ((err = inflateInit(&strm)) != Z_OK)
                {
                    return RPXError::ZLIB_ERROR;
                }
                while(data_size > 0)
                {
                    block_size = CHUNK;
                    if(data_size<block_size)
                        block_size = data_size;
                    data_size -= block_size;
                    in.read(buff_in, block_size);
                    strm.avail_in = in.gcount();
                    strm.next_in = reinterpret_cast<Bytef*>(buff_in);
                    do
                    {
                        strm.avail_out = CHUNK;
                        strm.next_out = reinterpret_cast<Bytef*>(buff_out);
                        err = inflate(&strm, Z_NO_FLUSH);
                        if (err != Z_OK && err != Z_BUF_ERROR && err != Z_STREAM_END)
                        {
                            return RPXError::ZLIB_ERROR;
                        }
                        have = CHUNK - strm.avail_out;
                        out.write(buff_out, have);
                        crcs[shdr_index->index] = crc32_rpx(crcs[shdr_index->index], reinterpret_cast<uint8_t*>(buff_out), have);
                    }while(strm.avail_out == 0);
                }
                if ((err = inflateEnd(&strm)) != Z_OK)
                {
                    return RPXError::ZLIB_ERROR;
                }
                shdr_table[shdr_index->index].sh_flags &= ~SHF_RPL_ZLIB;
            }
            else
            {
                uint32_t data_size = shdr_table[shdr_index->index].sh_size;
                uint32_t block_size = CHUNK;
                while(data_size>0)
                {
                    char data[CHUNK];
                    block_size = CHUNK;
                    if(data_size < block_size)
                        block_size = data_size;
                    data_size -= block_size;
                    in.read(data, block_size);
                    out.write(data, block_size);
                    crcs[shdr_index->index] = crc32_rpx(crcs[shdr_index->index], reinterpret_cast<uint8_t*>(data), block_size);
                }
            }
            while (out.tellp() % 0x40 != 0) out.put(0);
            if(shdr_table[shdr_index->index].sh_type == SectionType::SHT_RPL_CRCS)
            {
                crcs[shdr_index->index] = 0;
                crc_data_offset = shdr_table[shdr_index->index].sh_offset;
            }
        }
        out.seekp(ehdr.e_shoff);
        for (uint32_t i=0; i<ehdr.e_shnum; i++)
        {
            auto sh_name = Utility::byteswap(shdr_table[i].sh_name);
            auto sh_type = Utility::byteswap(static_cast<std::underlying_type_t<SectionType>>(shdr_table[i].sh_type));
            auto sh_flags = Utility::byteswap(shdr_table[i].sh_flags);
            auto sh_addr = Utility::byteswap(shdr_table[i].sh_addr);
            auto sh_offset = Utility::byteswap(shdr_table[i].sh_offset);
            auto sh_size = Utility::byteswap(shdr_table[i].sh_size);
            auto sh_link = Utility::byteswap(shdr_table[i].sh_link);
            auto sh_info = Utility::byteswap(shdr_table[i].sh_info);
            auto sh_addralign = Utility::byteswap(shdr_table[i].sh_addralign);
            auto sh_entsize = Utility::byteswap(shdr_table[i].sh_entsize);

            out.write(reinterpret_cast<char*>(&sh_name), sizeof(sh_name));
            out.write(reinterpret_cast<char*>(&sh_type), sizeof(sh_type));
            out.write(reinterpret_cast<char*>(&sh_flags), sizeof(sh_flags));
            out.write(reinterpret_cast<char*>(&sh_addr), sizeof(sh_addr));
            out.write(reinterpret_cast<char*>(&sh_offset), sizeof(sh_offset));
            out.write(reinterpret_cast<char*>(&sh_size), sizeof(sh_size));
            out.write(reinterpret_cast<char*>(&sh_link), sizeof(sh_link));
            out.write(reinterpret_cast<char*>(&sh_info), sizeof(sh_info));
            out.write(reinterpret_cast<char*>(&sh_addralign), sizeof(sh_addralign));
            out.write(reinterpret_cast<char*>(&sh_entsize), sizeof(sh_entsize));
        }
        
        out.seekp(crc_data_offset);
        for (uint32_t i = 0; i < ehdr.e_shnum; i++) {
            auto crc = Utility::byteswap(crcs[i]);
            out.write(reinterpret_cast<char*>(&crc), sizeof(crc));
        }
        delete[]crcs;
        delete[]shdr_table;
        shdr_table_index.clear();
        return RPXError::NONE;
    }

    RPXError rpx_compress(std::istream& in, std::ostream& out)
    {
        Elf32_Ehdr ehdr;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_ident[0]), 0x10)) return RPXError::REACHED_EOF;
        if (std::strncmp(reinterpret_cast<char*>(&ehdr.e_ident[0]), "\x7F""ELF", 4)) return RPXError::NOT_RPX;

        if (!in.read(reinterpret_cast<char*>(&ehdr.e_type), sizeof(ehdr.e_type))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_machine), sizeof(ehdr.e_machine))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_version), sizeof(ehdr.e_version))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_entry), sizeof(ehdr.e_entry))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_phoff), sizeof(ehdr.e_phoff))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_shoff), sizeof(ehdr.e_shoff))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_flags), sizeof(ehdr.e_flags))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_ehsize), sizeof(ehdr.e_ehsize))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_phentsize), sizeof(ehdr.e_phentsize))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_phnum), sizeof(ehdr.e_phnum))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_shentsize), sizeof(ehdr.e_shentsize))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_shnum), sizeof(ehdr.e_shnum))) return RPXError::REACHED_EOF;
        if (!in.read(reinterpret_cast<char*>(&ehdr.e_shstrndx), sizeof(ehdr.e_shstrndx))) return RPXError::REACHED_EOF;

        Utility::byteswap_inplace(ehdr.e_type);
        Utility::byteswap_inplace(ehdr.e_machine);
        Utility::byteswap_inplace(ehdr.e_version);
        Utility::byteswap_inplace(ehdr.e_entry);
        Utility::byteswap_inplace(ehdr.e_phoff);
        Utility::byteswap_inplace(ehdr.e_shoff);
        Utility::byteswap_inplace(ehdr.e_flags);
        Utility::byteswap_inplace(ehdr.e_ehsize);
        Utility::byteswap_inplace(ehdr.e_phentsize);
        Utility::byteswap_inplace(ehdr.e_phnum);
        Utility::byteswap_inplace(ehdr.e_shentsize);
        Utility::byteswap_inplace(ehdr.e_shnum);
        Utility::byteswap_inplace(ehdr.e_shstrndx);

        if (ehdr.e_type != 0xFE01) return RPXError::UNKNOWN_E_TYPE;

        uint32_t shdr_data_elf_offset = ehdr.e_shoff + ehdr.e_shnum * ehdr.e_shentsize;
        out.write(reinterpret_cast<char*>(&ehdr.e_ident[0]), 0x10);

        auto e_type = Utility::byteswap(ehdr.e_type);
        auto e_machine = Utility::byteswap(ehdr.e_machine);
        auto e_version = Utility::byteswap(ehdr.e_version);
        auto e_entry = Utility::byteswap(ehdr.e_entry);
        auto e_phoff = Utility::byteswap(ehdr.e_phoff);
        auto e_shoff = Utility::byteswap(ehdr.e_shoff);
        auto e_flags = Utility::byteswap(ehdr.e_flags);
        auto e_ehsize = Utility::byteswap(ehdr.e_ehsize);
        auto e_phentsize = Utility::byteswap(ehdr.e_phentsize);
        auto e_phnum = Utility::byteswap(ehdr.e_phnum);
        auto e_shentsize = Utility::byteswap(ehdr.e_shentsize);
        auto e_shnum = Utility::byteswap(ehdr.e_shnum);
        auto e_shstrndx = Utility::byteswap(ehdr.e_shstrndx);

        out.write(reinterpret_cast<char*>(&e_type), sizeof(e_type));
        out.write(reinterpret_cast<char*>(&e_machine), sizeof(e_machine));
        out.write(reinterpret_cast<char*>(&e_version), sizeof(e_version));
        out.write(reinterpret_cast<char*>(&e_entry), sizeof(e_entry));
        out.write(reinterpret_cast<char*>(&e_phoff), sizeof(e_phoff));
        out.write(reinterpret_cast<char*>(&e_shoff), sizeof(e_shoff));
        out.write(reinterpret_cast<char*>(&e_flags), sizeof(e_flags));
        out.write(reinterpret_cast<char*>(&e_ehsize), sizeof(e_ehsize));
        out.write(reinterpret_cast<char*>(&e_phentsize), sizeof(e_phentsize));
        out.write(reinterpret_cast<char*>(&e_phnum), sizeof(e_phnum));
        out.write(reinterpret_cast<char*>(&e_shentsize), sizeof(e_shentsize));
        out.write(reinterpret_cast<char*>(&e_shnum), sizeof(e_shnum));
        out.write(reinterpret_cast<char*>(&e_shstrndx), sizeof(e_shstrndx));

        const uint32_t zero = 0x00000000;
        out.write(reinterpret_cast<const char*>(&zero), 4);
        out.write(reinterpret_cast<const char*>(&zero), 4);
        out.write(reinterpret_cast<const char*>(&zero), 4);

        uint32_t crc_data_offset = 0;
        uint32_t *crcs = new uint32_t[ehdr.e_shnum];
        std::vector<Elf32_Shdr_Sort> shdr_table_index;
        Elf32_Shdr *shdr_table = new Elf32_Shdr[ehdr.e_shnum];
        while(static_cast<uint32_t>(out.tellp()) < shdr_data_elf_offset) out.put(0);
        in.seekg(ehdr.e_shoff);
        for (uint32_t i=0; i<ehdr.e_shnum; i++)
        {
            crcs[i] = 0;

            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_name), sizeof(shdr_table[i].sh_name))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_type), sizeof(shdr_table[i].sh_type))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_flags), sizeof(shdr_table[i].sh_flags))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_addr), sizeof(shdr_table[i].sh_addr))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_offset), sizeof(shdr_table[i].sh_offset))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_size), sizeof(shdr_table[i].sh_size))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_link), sizeof(shdr_table[i].sh_link))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_info), sizeof(shdr_table[i].sh_info))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_addralign), sizeof(shdr_table[i].sh_addralign))) return RPXError::REACHED_EOF;
            if (!in.read(reinterpret_cast<char*>(&shdr_table[i].sh_entsize), sizeof(shdr_table[i].sh_entsize))) return RPXError::REACHED_EOF;

            Utility::byteswap_inplace(shdr_table[i].sh_name);
            shdr_table[i].sh_type = static_cast<SectionType>(Utility::byteswap(static_cast<std::underlying_type_t<SectionType>>(shdr_table[i].sh_type)));
            Utility::byteswap_inplace(shdr_table[i].sh_flags);
            Utility::byteswap_inplace(shdr_table[i].sh_addr);
            Utility::byteswap_inplace(shdr_table[i].sh_offset);
            Utility::byteswap_inplace(shdr_table[i].sh_size);
            Utility::byteswap_inplace(shdr_table[i].sh_link);
            Utility::byteswap_inplace(shdr_table[i].sh_info);
            Utility::byteswap_inplace(shdr_table[i].sh_addralign);
            Utility::byteswap_inplace(shdr_table[i].sh_entsize);

            if (shdr_table[i].sh_offset != 0)
            {
                Elf32_Shdr_Sort shdr_index;
                shdr_index.index = i;
                shdr_index.sh_offset = shdr_table[i].sh_offset;
                shdr_table_index.push_back(shdr_index);
            }
        }
        std::sort(shdr_table_index.begin(), shdr_table_index.end(), SortFunc);
        for(std::vector<Elf32_Shdr_Sort>::iterator shdr_index=shdr_table_index.begin();shdr_index!=shdr_table_index.end();shdr_index++)
        {
            pos = shdr_table[shdr_index->index].sh_offset; 
            in.seekg(pos);
            shdr_table[shdr_index->index].sh_offset = out.tellp();
            if ((shdr_table[shdr_index->index].sh_type == SectionType::SHT_RPL_FILEINFO)||
                (shdr_table[shdr_index->index].sh_type == SectionType::SHT_RPL_CRCS)||
                ((shdr_table[shdr_index->index].sh_flags & SHF_RPL_ZLIB) == SHF_RPL_ZLIB))
            {
                uint32_t data_size = shdr_table[shdr_index->index].sh_size;
                uint32_t block_size = CHUNK;
                while(data_size>0)
                {
                    char data[CHUNK];
                    block_size = CHUNK;
                    if(data_size<block_size)
                        block_size = data_size;
                    data_size -= block_size;
                    in.read(data, block_size);
                    out.write(data, block_size);
                    crcs[shdr_index->index] = crc32_rpx(crcs[shdr_index->index], reinterpret_cast<uint8_t*>(data), block_size);
                }
            }
            else
            {
                uint32_t data_size = shdr_table[shdr_index->index].sh_size;
                uint32_t block_size = CHUNK;
                uint32_t have;
                z_stream strm;
                char buff_in[CHUNK];
                char buff_out[CHUNK];
                strm.zalloc = Z_NULL;
                strm.zfree = Z_NULL;
                strm.opaque = Z_NULL;
                strm.avail_in = 0;
                strm.next_in = Z_NULL;
                if(data_size<CHUNK)
                {
                    block_size = data_size;
                    deflateInit(&strm, LEVEL);
                    in.read(buff_in, block_size);
                    strm.avail_in = in.gcount();
                    crcs[shdr_index->index] = crc32_rpx(crcs[shdr_index->index], reinterpret_cast<uint8_t*>(buff_in), block_size);
                    strm.next_in = reinterpret_cast<Bytef*>(buff_in);
                    strm.avail_out = CHUNK;
                    strm.next_out = reinterpret_cast<Bytef*>(buff_out);
                    deflate(&strm, Z_FINISH);
                    have = CHUNK - strm.avail_out;
                    if(have + 4 < block_size)
                    {
                        auto data_size_BE = Utility::byteswap(data_size);
                        out.write(reinterpret_cast<char*>(&data_size_BE), sizeof(data_size_BE));
                        out.write(buff_out, have);
                        shdr_table[shdr_index->index].sh_size = have + 4;
                        shdr_table[shdr_index->index].sh_flags |= SHF_RPL_ZLIB;
                    }
                    else
                        out.write(buff_in, block_size);
                    deflateEnd(&strm);
                }
                else
                {
                    int32_t flush = Z_NO_FLUSH;
                    uint32_t compress_size = 4;

                    auto data_size_BE = Utility::byteswap(data_size);
                    out.write(reinterpret_cast<char*>(&data_size_BE), sizeof(data_size_BE));

                    deflateInit(&strm, LEVEL);
                    while(data_size>0)
                    {
                        block_size = CHUNK;
                        flush = Z_NO_FLUSH;
                        if(data_size <= block_size)
                        {
                            block_size = data_size;
                            flush = Z_FINISH;
                        }
                        data_size -= block_size;
                        in.read(buff_in, block_size);
                        strm.avail_in = in.gcount();
                        crcs[shdr_index->index] = crc32_rpx(crcs[shdr_index->index], reinterpret_cast<uint8_t*>(buff_in), block_size);
                        strm.next_in = reinterpret_cast<Bytef*>(buff_in);
                        do{
                            strm.avail_out = CHUNK;
                            strm.next_out = reinterpret_cast<Bytef*>(buff_out);
                            deflate(&strm, flush);
                            have = CHUNK - strm.avail_out;
                            out.write(buff_out, have);
                            compress_size += have;
                        }while(strm.avail_out == 0);
                    }
                    deflateEnd(&strm);
                    shdr_table[shdr_index->index].sh_size = compress_size;
                    shdr_table[shdr_index->index].sh_flags |= SHF_RPL_ZLIB;
                }
            }
            while(out.tellp() % 0x40 != 0) out.put(0);
            if(shdr_table[shdr_index->index].sh_type == SectionType::SHT_RPL_CRCS)
            {
                crcs[shdr_index->index] = 0;
                crc_data_offset = shdr_table[shdr_index->index].sh_offset;
            }
        }
        out.seekp(ehdr.e_shoff);
        for (uint32_t i=0; i<ehdr.e_shnum; i++)
        {
            auto sh_name = Utility::byteswap(shdr_table[i].sh_name);
            auto sh_type = Utility::byteswap(static_cast<std::underlying_type_t<SectionType>>(shdr_table[i].sh_type));
            auto sh_flags = Utility::byteswap(shdr_table[i].sh_flags);
            auto sh_addr = Utility::byteswap(shdr_table[i].sh_addr);
            auto sh_offset = Utility::byteswap(shdr_table[i].sh_offset);
            auto sh_size = Utility::byteswap(shdr_table[i].sh_size);
            auto sh_link = Utility::byteswap(shdr_table[i].sh_link);
            auto sh_info = Utility::byteswap(shdr_table[i].sh_info);
            auto sh_addralign = Utility::byteswap(shdr_table[i].sh_addralign);
            auto sh_entsize = Utility::byteswap(shdr_table[i].sh_entsize);

            out.write(reinterpret_cast<char*>(&sh_name), sizeof(sh_name));
            out.write(reinterpret_cast<char*>(&sh_type), sizeof(sh_type));
            out.write(reinterpret_cast<char*>(&sh_flags), sizeof(sh_flags));
            out.write(reinterpret_cast<char*>(&sh_addr), sizeof(sh_addr));
            out.write(reinterpret_cast<char*>(&sh_offset), sizeof(sh_offset));
            out.write(reinterpret_cast<char*>(&sh_size), sizeof(sh_size));
            out.write(reinterpret_cast<char*>(&sh_link), sizeof(sh_link));
            out.write(reinterpret_cast<char*>(&sh_info), sizeof(sh_info));
            out.write(reinterpret_cast<char*>(&sh_addralign), sizeof(sh_addralign));
            out.write(reinterpret_cast<char*>(&sh_entsize), sizeof(sh_entsize));
        }

        out.seekp(crc_data_offset);
        for (uint32_t i = 0; i < ehdr.e_shnum; i++) {
            auto crc = Utility::byteswap(crcs[i]);
            out.write(reinterpret_cast<char*>(&crc), sizeof(crc));
        }
        delete[]crcs;
        delete[]shdr_table;
        shdr_table_index.clear();
        return RPXError::NONE;
    }
}
