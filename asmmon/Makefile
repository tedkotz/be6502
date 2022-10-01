# Makefile to crosscompile using CC65

# This c runtime is based off the instruction to build a custom runtime for cc65 here:
# https://www.cc65.org/doc/customizing.html
EXEPKG=asmmon.bin
INCLUDES=../echo_console
LIBPKG=../echo_console/becrt.lib
ROMIMG=$(EXEPKG).rom.bin
PKG=$(EXEPKG)
EXESRCS=main.c vectors.s
CC=cc65
CFLAGS=-t none -Os --cpu 65c02 -T -g --include-dir $(INCLUDES)
ASM=ca65
ASMFLAGS=--cpu 65c02 -U -g --include-dir $(INCLUDES)
LD=ld65
AR=ar65
LIBS=

#DEPDIR=deps
#DEPS=$(SRCS:%$(SRCEXT)=$(DEPDIR)/%.d)
OBJDIR=obj
EXEOBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(patsubst %.s,$(OBJDIR)/%.o,$(EXESRCS)))
LIBOBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(patsubst %.s,$(OBJDIR)/%.o,$(LIBSRCS)))
ASMDIR=asm


MAPFILE=becrt.map
SRCS=$(EXESRCS) $(LIBSRCS)
ASMS=$(patsubst %.c,$(ASMDIR)/%.s,$(patsubst %.s,$(ASMDIR)/%.s,$(SRCS)))
#DOCDIR=doc
#DOCCMD=doxygen
#DOCCFG=Doxyfile
SED=sed
MKDIR=@mkdir
CP=cp

pkg: $(PKG)

$(EXEPKG): $(LIBPKG) $(EXEOBJS)
	@echo "Generating $@"
	$(LD) -C be6502.cfg -m $(MAPFILE) $(EXEOBJS) $(LIBPKG) --lib none.lib -o $@
	grep "Segment list:" -A12 $(MAPFILE)

$(ROMIMG): $(EXEPKG)

test: $(ROMIMG)
	hexdump -C $<

install: $(ROMIMG)
	minipro -p AT28C256 -w $<

## OBJ management
$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/%.o: $(ASMDIR)/%.s | $(OBJDIR) $(ASMDIR)
	@echo "ASM $<"
	$(ASM) $(ASMFLAGS) $< -o $@

clean-obj:
	rm -rf $(OBJDIR)


## ASM management
$(ASMDIR):
	$(MKDIR) $(ASMDIR)

$(ASMDIR)/%.s: %.c | $(ASMDIR)
	@echo "CC $<"
	$(CC) $(CFLAGS) $< -o $@

$(ASMDIR)/%.s: %.s | $(ASMDIR)
	@echo "CP $<"
	$(CP) $< $@

asms: $(ASMS)

clean-asm:
	rm -rf $(ASMDIR)

## DEP management
# $(DEPDIR):
# 	$(MKDIR) $(DEPDIR)
#
# $(DEPDIR)/%.d: %.c | $(DEPDIR) $(ASMDIR)
# 	$(CC) $(CFLAGS) $< --create-full-dep $@ -o $(ASMDIR)/
# 	$(SED) -i 's+\($*\)\.o[ :]*+$(OBJDIR)/\1.o $@ : +g' $@
# --create-full-dep
#--dep-target target
#
# $(DEPDIR)/%.d: %.s | $(DEPDIR)
# 	$(CC) $(CFLAGS) -c $< -MM -o $@
# 	$(SED) -i 's+\($*\)\.o[ :]*+$(OBJDIR)/\1.o $@ : +g' $@
# --create-full-dep

#clean-dep:
#	rm -rf $(DEPDIR)

## DOC management
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

## CLEAN UP
clean: clean-obj clean-asm
	rm -rf *~

#clean-pkg: clean clean-dep
clean-pkg: clean
	rm -rf $(PKG) $(MAPFILE) $(LIBPKG) $(ROMIMG)

rebuild: clean-pkg pkg

#all: $(PKG) docs
all: $(PKG)

#clean-all: clean-pkg clean-docs
clean-all: clean-pkg

rebuild-all: clean-all all

#include $(DEPS)

$(V).SILENT:
