SRC = src
FLAG = -s
REPORT = report.tex
REPORT_OUT := $(filter-out $(REPORT), $(wildcard report.*))
TARGET = calculator

all:$(TARGET)

$(TARGET):
	$(MAKE) -C $(SRC)

run: $(SRC)
	@$(MAKE) -C $(SRC) $(FLAG) run

test: $(SRC)
	@$(MAKE) -C $(SRC) $(FLAG) test

clean:
	@$(MAKE) -C $(SRC) $(FLAG) clean
	@rm -f $(REPORT_OUT)

report:
	xelatex $(REPORT)