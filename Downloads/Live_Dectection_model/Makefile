.PHONY: help install test clean docker-build docker-run

help: ## Show this help message
	@echo "YOLOv13 Live Detection Suite - Available Commands:"
	@echo ""
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

install: ## Install dependencies
	pip install -r requirements.txt

install-dev: ## Install development dependencies
	pip install -r requirements.txt
	pip install pytest pytest-cov black flake8 mypy pre-commit

test: ## Run tests
	pytest

format: ## Format code with black
	black .

lint: ## Lint code with flake8
	flake8 .

type-check: ## Run type checking with mypy
	mypy .

clean: ## Clean up generated files
	find . -type f -name "*.pyc" -delete
	find . -type d -name "__pycache__" -delete
	find . -type d -name "*.egg-info" -exec rm -rf {} +
	rm -rf build/ dist/ .pytest_cache/ .coverage htmlcov/

docker-build: ## Build Docker image
	docker build -t yolov13-detection-suite .

docker-run: ## Run Docker container
	docker run -it --rm -p 8000:8000 yolov13-detection-suite

docker-run-gpu: ## Run Docker container with GPU support
	docker run -it --rm --gpus all -p 8000:8000 yolov13-detection-suite

docker-compose-up: ## Start services with Docker Compose
	docker-compose up -d

docker-compose-down: ## Stop services with Docker Compose
	docker-compose down

setup: ## Initial setup
	python -m venv venv
	@echo "Virtual environment created. Activate it with:"
	@echo "  source venv/bin/activate  # On Unix/macOS"
	@echo "  venv\\Scripts\\activate     # On Windows"
	@echo ""
	@echo "Then run: make install"

run: ## Run the detection suite
	python webcam_detection_enhanced.py --models yolov13s.pt

run-nano: ## Run with nano model (fastest)
	python webcam_detection_enhanced.py --models yolov13n.pt

run-ensemble: ## Run with ensemble detection
	python webcam_detection_enhanced.py --models yolov13n.pt yolov13s.pt --ensemble wbf

