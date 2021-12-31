# Makefile to crosscompile using CC65
EXEPKG=becrt.bin
LIBPKG=becrt.lib
ROMIMG=$(EXEPKG).rom.bin
PKG=$(EXEPKG)
LIBSRCS=crt0.s pckybd.s interrupt.s
EXESRCS=main.c vectors.s
CC=cc65
CFLAGS=-t none -O --cpu 65c02
ASM=ca65
ASMFLAGS=--cpu 65c02
LD=ld65
AR=ar65
LIBS=

#DEPDIR=deps
#DEPS=$(SRCS:%$(SRCEXT)=$(DEPDIR)/%.d)
OBJDIR=obj
EXEOBJS=$(patsubst %.s,$(OBJDIR)/%.o,$(patsubst %.c,$(OBJDIR)/%.o,$(EXESRCS)))
LIBOBJS=$(patsubst %.s,$(OBJDIR)/%.o,$(patsubst %.c,$(OBJDIR)/%.o,$(LIBSRCS)))
ASMDIR=asm

MAPFILE=becrt.map
#ASMS=$(SRCS:%$(SRCEXT)=$(ASMDIR)/%.s)
#DOCDIR=doc
#DOCCMD=doxygen
#DOCCFG=Doxyfile
SED=sed
MKDIR=@mkdir
CP=cp

pkg: $(PKG)

$(LIBPKG): $(LIBOBJS)
	@echo "Generating $@"
	rm -f $@
	$(AR) a $@ $(LIBOBJS)

$(EXEPKG): $(LIBPKG) $(EXEOBJS)
	@echo "Generating $@"
	$(LD) -C be6502.cfg -m $(MAPFILE) $(EXEOBJS) $(LIBPKG) --lib none.lib -o $@

$(ROMIMG): $(EXEPKG)

hexdump: $(ROMIMG)
	hexdump -C $<

program: $(ROMIMG)
	minipro -p AT28C256 -w $<

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/%.o: $(ASMDIR)/%.s | $(OBJDIR) $(ASMDIR)
	@echo "ASM $<"
	$(ASM) $(ASMFLAGS) $< -o $@

$(ASMDIR):
	$(MKDIR) $(ASMDIR)

$(ASMDIR)/%.s: %.c | $(ASMDIR)
	@echo "CC $<"
	$(CC) $(CFLAGS) $< -o $@

$(ASMDIR)/%.s: %.s | $(ASMDIR)
	@echo "CP $<"
	$(CP) $< $@

# $(DEPDIR):
# 	$(MKDIR) $(DEPDIR)
#
# $(DEPDIR)/%.d: %.c | $(DEPDIR) $(ASMDIR)
# 	$(CC) $(CFLAGS) $< --create-full-dep $@ -o $(ASMDIR)
# 	$(SED) -i 's+\($*\)\.o[ :]*+$(OBJDIR)/\1.o $@ : +g' $@
# --create-full-dep
#
# $(DEPDIR)/%.d: %.s | $(DEPDIR)
# 	$(CC) $(CFLAGS) -c $< -MM -o $@
# 	$(SED) -i 's+\($*\)\.o[ :]*+$(OBJDIR)/\1.o $@ : +g' $@
# --create-full-dep

#asms: $(ASMS)


#test: $(PKG)
#	./$(PKG)

#install: $(PKG)
#	cp $(PKG) $(PREFIX)/bin/
#	cp $(PKG)rc $(CONFIGDIR)/

clean-asm:
	rm -rf $(ASMDIR)

clean-obj:
	rm -rf $(OBJDIR)

#clean-dep:
#	rm -rf $(DEPDIR)

clean: clean-obj clean-asm
	rm -rf *~

#clean-pkg: clean clean-dep
clean-pkg: clean
	rm -rf $(PKG) $(MAPFILE) $(LIBPKG) $(ROMIMG)

rebuild: clean-pkg pkg

#$(DOCCFG):
#	$(DOCCMD) -g $(DOCCFG)
#	$(SED) -i 's+^OUTPUT_DIRECTORY *=.*$$+OUTPUT_DIRECTORY       = $(DOCDIR)+g' $(DOCCFG)
#	$(SED) -i 's+^PROJECT_NAME *=.*$$+PROJECT_NAME           = "$(PKG)"+g' $(DOCCFG)
#	$(SED) -i 's+^GENERATE_LATEX *=.*$$+GENERATE_LATEX         = NO+g' $(DOCCFG)
#	$(SED) -i 's+^SOURCE_BROWSER *=.*$$+SOURCE_BROWSER         = YES+g' $(DOCCFG)
#	$(SED) -i 's+^GENERATE_TREEVIEW *=.*$$+GENERATE_TREEVIEW      = YES+g' $(DOCCFG)
##	$(SED) -i 's+^PLANTUML_JAR_PATH *=.*$$+PLANTUML_JAR_PATH      = /usr/share/plantuml/plantuml.jar+g' $(DOCCFG)
#
#docs: $(DOCCFG)
#	$(DOCCMD) $(DOCCFG)
#
#clean-docs:
#	rm -rf $(DOCDIR)
#
#rebuild-docs: clean-docs docs

#all: $(PKG) docs
all: $(PKG)

#clean-all: clean-pkg clean-docs
clean-all: clean-pkg

rebuild-all: clean-all all

#include $(DEPS)

$(V).SILENT:

#!/bin/sh

# This c runtime is based off the instruction to build a custom runtime for cc65 here:
# https://www.cc65.org/doc/customizing.html

#  cc65 -t none -O --cpu 65c02 main.c
#  ca65 --cpu 65c02 vectors.s
#  ca65 --cpu 65c02 main.s
#  ca65 --cpu 65c02 crt0.s
#  ca65 --cpu 65c02 pckybd.s
#  ca65 --cpu 65c02 interrupt.s
#  rm -f tkotz.lib
#  ar65 a tkotz.lib crt0.o pckybd.o interrupt.o
#  ld65 -v -C be6502.cfg -m memory.map main.o vectors.o tkotz.lib --lib none.lib
#  #ld65 -C be6502.cfg -m memory.map main.o vectors.o crt0.o interrupt.o be6502.lib pckybd.o
#  #hexdump -C a.out.rom.bin
#  ## minipro -p AT28C256 -w a.out.rom.bin
