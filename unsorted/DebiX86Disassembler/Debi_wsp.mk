.PHONY: clean All

All:
	@echo ----------Building project:[ Debi - Debug ]----------
	@cd "Debi" && "$(MAKE)" -f "Debi.mk"
clean:
	@echo ----------Cleaning project:[ Debi - Debug ]----------
	@cd "Debi" && "$(MAKE)" -f "Debi.mk" clean
