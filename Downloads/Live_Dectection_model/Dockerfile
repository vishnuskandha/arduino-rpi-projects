# 🐳 YOLOv13 Live Detection Suite Docker Image
FROM python:3.11-slim

# Set environment variables
ENV PYTHONUNBUFFERED=1
ENV PYTHONDONTWRITEBYTECODE=1

# Install system dependencies
RUN apt-get update && apt-get install -y \
    libgl1-mesa-glx \
    libglib2.0-0 \
    libsm6 \
    libxext6 \
    libxrender-dev \
    libgomp1 \
    libgthread-2.0-0 \
    libgtk-3-0 \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libv4l-dev \
    libxvidcore-dev \
    libx264-dev \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy requirements and install Python dependencies
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copy source code
COPY . .

# Create non-root user
RUN useradd -m -u 1000 yolov13 && \
    chown -R yolov13:yolov13 /app
USER yolov13

# Expose port for web interface (if applicable)
EXPOSE 8000

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD python -c "import cv2; print('Health check passed')" || exit 1

# Default command
CMD ["python", "webcam_detection_enhanced.py", "--help"]

# Labels for better organization
LABEL maintainer="Your Name <your.email@example.com>"
LABEL version="1.2.0"
LABEL description="YOLOv13 Live Detection Suite - The Ultimate Real-Time Object Detection Experience"
LABEL org.opencontainers.image.source="https://github.com/yourusername/yolov13-detection-suite"
LABEL org.opencontainers.image.licenses="AGPL-3.0"
