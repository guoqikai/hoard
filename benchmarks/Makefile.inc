INCLUDES = $(TOPDIR)/include
LIBDIR = $(TOPDIR)/util
LIBS = -lmmutil -lpthread -lm
LIBS_DBG = -lmmutil_dbg -lpthread -lm

DEPENDS = $(TARGET).c $(LIBDIR)/libmmutil.a $(INCLUDES)/mm_thread.h $(INCLUDES)/timer.h
DEPENDS_DBG = $(TARGET).c $(LIBDIR)/libmmutil_dbg.a $(INCLUDES)/mm_thread.h $(INCLUDES)/timer.h

CC = gcc
CC_FLAGS = -O3 -DNDEBUG -I$(INCLUDES) -L $(LIBDIR)
CC_DBG_FLAGS = -g -I$(INCLUDES) -L $(LIBDIR)

all: $(TARGET)-kheap $(TARGET)-libc $(TARGET)-hoard-alloc

debug: $(TARGET)-kheap-dbg $(TARGET)-libc-dbg $(TARGET)-hoard-alloc-dbg

# Allocator based on OS/161 kheap

$(TARGET)-kheap: $(DEPENDS) $(TOPDIR)/allocators/alloclibs/libkheap.a
	$(CC) $(CC_FLAGS) -o $(@) $(TARGET).c $(TOPDIR)/allocators/alloclibs/libkheap.a $(LIBS)

$(TARGET)-kheap-dbg: $(DEPENDS_DBG) $(TOPDIR)/allocators/alloclibs/libkheap_dbg.a 
	$(CC) $(CC_DBG_FLAGS) -o $(@) $(TARGET).c $(TOPDIR)/allocators/alloclibs/libkheap_dbg.a $(LIBS_DBG)

# Allocator using libc malloc/free inside mm_malloc/mm_free wrappers

$(TARGET)-libc: $(DEPENDS) $(TOPDIR)/allocators/alloclibs/libmmlibc.a
	$(CC) $(CC_FLAGS) -o $(@) $(TARGET).c $(TOPDIR)/allocators/alloclibs/libmmlibc.a $(LIBS)

$(TARGET)-libc-dbg: $(DEPENDS_DBG) $(TOPDIR)/allocators/alloclibs/libmmlibc_dbg.a
	$(CC) $(CC_DBG_FLAGS) -o $(@) $(TARGET).c $(TOPDIR)/allocators/alloclibs/libmmlibc_dbg.a $(LIBS_DBG)

# Allocator using hoard

$(TARGET)-hoard-alloc: $(DEPENDS) $(TOPDIR)/allocators/alloclibs/libhoard-alloc.a
	$(CC) $(CC_FLAGS) -o $(@) $(TARGET).c $(TOPDIR)/allocators/alloclibs/libhoard-alloc.a $(LIBS)

$(TARGET)-hoard-alloc-dbg: $(DEPENDS_DBG) $(TOPDIR)/allocators/alloclibs/libhoard-alloc_dbg.a
	$(CC) $(CC_DBG_FLAGS) -o $(@) $(TARGET).c $(TOPDIR)/allocators/alloclibs/libhoard-alloc_dbg.a $(LIBS_DBG)

# Cleanup
clean:
	rm -f $(TARGET)-* *~
