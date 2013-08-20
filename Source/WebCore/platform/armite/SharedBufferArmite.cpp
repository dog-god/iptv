/*
 * Copyright (C) 2012 armite@126.com.
 */

#include "config.h"
#include "SharedBuffer.h"

#include <wtf/text/CString.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace WebCore {

PassRefPtr<SharedBuffer> SharedBuffer::createWithContentsOfFile(const String& filePath)
{
    FILE* file;
    struct stat fileStat;
    RefPtr<SharedBuffer> result;

    if (filePath.isEmpty())
        return 0;

    if (!(file = fopen(filePath.utf8().data(), "rb")))
        return 0;

    if (fstat(fileno(file), &fileStat)) {
        fclose(file);
        return 0;
    }

    result = SharedBuffer::create();
    result->m_buffer.resize(fileStat.st_size);
    if (result->m_buffer.size() != static_cast<unsigned>(fileStat.st_size)) {
        fclose(file);
        return 0;
    }

    fread(result->m_buffer.data(), 1, fileStat.st_size, file);
    fclose(file);

    return result.release();
}

} // namespace WebCore



