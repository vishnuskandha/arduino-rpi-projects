#!/usr/bin/env python3
"""
YOLOv13 Live Detection Suite
The Ultimate Real-Time Object Detection Experience
"""

from setuptools import setup, find_packages

# Read the README file
with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()

# Read requirements
with open("requirements.txt", "r", encoding="utf-8") as fh:
    requirements = [line.strip() for line in fh if line.strip() and not line.startswith("#")]

setup(
    name="yolov13-detection-suite",
    version="1.2.0",
    author="Your Name",
    author_email="your.email@example.com",
    description="The Ultimate Real-Time Object Detection Experience with YOLOv13",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/yourusername/yolov13-detection-suite",
    packages=find_packages(),
    classifiers=[
        "Development Status :: 5 - Production/Stable",
        "Intended Audience :: Developers",
        "Intended Audience :: Science/Research",
        "License :: OSI Approved :: GNU Affero General Public License v3",
        "Operating System :: OS Independent",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
        "Topic :: Scientific/Engineering :: Artificial Intelligence",
        "Topic :: Scientific/Engineering :: Image Processing",
        "Topic :: Software Development :: Libraries :: Python Modules",
        "Topic :: Multimedia :: Video :: Capture",
    ],
    python_requires=">=3.8",
    install_requires=requirements,
    extras_require={
        "dev": [
            "pytest>=7.0.0",
            "pytest-cov>=4.0.0",
            "black>=23.0.0",
            "flake8>=6.0.0",
            "pre-commit>=3.0.0",
            "mypy>=1.0.0",
        ],
        "gpu": [
            "torch>=2.2.0+cu118",
            "torchvision>=0.17.0+cu118",
        ],
    },
    entry_points={
        "console_scripts": [
            "yolov13-detect=webcam_detection_enhanced:main",
            "yolov13-webcam=webcam_detection_enhanced:main",
        ],
    },
    include_package_data=True,
    package_data={
        "": ["*.yaml", "*.yml", "*.json"],
    },
    keywords=[
        "yolo", "object-detection", "computer-vision", "deep-learning",
        "real-time", "ai", "machine-learning", "opencv", "pytorch"
    ],
    project_urls={
        "Homepage": "https://github.com/yourusername/yolov13-detection-suite",
        "Documentation": "https://yolov13-detection-suite.readthedocs.io",
        "Repository": "https://github.com/yourusername/yolov13-detection-suite.git",
        "Bug Tracker": "https://github.com/yourusername/yolov13-detection-suite/issues",
        "Release Notes": "https://github.com/yourusername/yolov13-detection-suite/releases",
    },
)

