# 🤝 Contributing to YOLOv13 Live Detection Suite

First off, thank you for considering contributing to YOLOv13 Live Detection Suite! 🎉

It's people like you who make YOLOv13 Live Detection Suite such a great tool.

## 📋 Table of Contents

- [Code of Conduct](#code-of-conduct)
- [I don't want to read this whole thing, I just have a question!](#i-dont-want-to-read-this-whole-thing-i-just-have-a-question)
- [What should I know before I get started?](#what-should-i-know-before-i-get-started)
- [How Can I Contribute?](#how-can-i-contribute)
- [Styleguides](#styleguides)
- [Additional Notes](#additional-notes)

## 📜 Code of Conduct

This project and everyone participating in it is governed by our Code of Conduct. By participating, you are expected to uphold this code. Please report unacceptable behavior to [your-email@example.com](mailto:your-email@example.com).

## ❓ I don't want to read this whole thing, I just have a question!

> **Note:** Please don't file an issue to ask a question. You'll get faster results by using the resources below.

We have an official message board with a detailed FAQ and where the community chimes in with helpful advice if you have questions.

* [GitHub Discussions](https://github.com/yourusername/yolov13-detection-suite/discussions) - Ask questions and discuss with the community
* [GitHub Issues](https://github.com/yourusername/yolov13-detection-suite/issues) - Report bugs or request features
* [Discord Community](https://discord.gg/your-server) - Real-time chat and support

## 🔍 What should I know before I get started?

### 🏗️ Project Structure

```
yolov13-detection-suite/
├── src/
│   └── yolov13_detection/
│       ├── __init__.py
│       ├── core.py          # Core detection engine
│       ├── webcam.py        # Webcam detection
│       ├── ensemble.py      # Ensemble detection methods
│       └── utils.py         # Utility functions
├── examples/                 # Example scripts and notebooks
├── tests/                   # Test suite
├── docs/                    # Documentation
├── requirements.txt          # Dependencies
└── README.md               # This file
```

### 🧪 Testing

We use pytest for testing. Before submitting a PR, please ensure all tests pass:

```bash
# Install test dependencies
pip install -r requirements-dev.txt

# Run tests
pytest

# Run with coverage
pytest --cov=yolov13_detection --cov-report=html
```

### 📝 Code Style

We use several tools to maintain code quality:

- **Black** for code formatting
- **Flake8** for linting
- **MyPy** for type checking
- **Pre-commit** hooks for automated checks

```bash
# Format code
black .

# Check types
mypy src/

# Run pre-commit hooks
pre-commit run --all-files
```

## 🚀 How Can I Contribute?

### 🐛 Reporting Bugs

Before creating bug reports, please check the issue list as you might find out that you don't need to create one. When you are creating a bug report, please include as many details as possible:

* **Use a clear and descriptive title** for the issue to identify the problem.
* **Describe the exact steps which reproduce the problem** in as many details as possible.
* **Provide specific examples to demonstrate the steps**. Include links to files or GitHub projects, or copy/pasteable snippets, which you use in those examples.
* **Describe the behavior you observed after following the steps** and point out what exactly is the problem with that behavior.
* **Explain which behavior you expected to see instead and why.**
* **Include details about your configuration and environment:**
  * Which version of YOLOv13 Live Detection Suite are you using?
  * What's the name and version of the OS you're using?
  * Are you running on CPU or GPU?
  * What Python version are you using?

### 💡 Suggesting Enhancements

If you have a suggestion for a new feature or enhancement, please:

* **Use a clear and descriptive title** for the issue to identify the suggestion.
* **Provide a step-by-step description of the suggested enhancement** in as many details as possible.
* **Provide specific examples to demonstrate the steps**.
* **Describe the current behavior and explain which behavior you expected to see instead and why.**
* **Include mockups, screenshots, or examples** if applicable.

### 🔧 Pull Requests

1. **Fork the repo** and create your branch from `main`.
2. **If you've added code that should be tested**, add tests.
3. **If you've changed APIs**, update the documentation.
4. **Ensure the test suite passes**.
5. **Make sure your code lints**.
6. **Issue that pull request!**

### 📚 Documentation

We love good documentation! Here are some areas where you can help:

* **Code comments** - Add clear, helpful comments to complex code
* **README updates** - Improve clarity, add examples, fix typos
* **API documentation** - Document new functions and classes
* **Tutorials** - Create example scripts or Jupyter notebooks
* **Translation** - Help translate documentation to other languages

### 🧪 Testing

* **Write tests** for new features
* **Improve test coverage** for existing code
* **Report bugs** you find while testing
* **Test on different platforms** (Windows, macOS, Linux)

### 🐛 Bug Fixes

* **Fix typos** in code or documentation
* **Fix broken links** in documentation
* **Fix minor bugs** you encounter
* **Improve error messages** to be more helpful

## 🎨 Styleguides

### Git Commit Messages

* Use the present tense ("Add feature" not "Added feature")
* Use the imperative mood ("Move cursor to..." not "Moves cursor to...")
* Limit the first line to 72 characters or less
* Reference issues and pull requests liberally after the first line

**Good examples:**
```
feat: add ensemble detection support

- Implement Weighted Boxes Fusion (WBF)
- Add support for multiple model inputs
- Include performance benchmarks

Closes #123
```

```
fix: resolve memory leak in GPU inference

- Clear CUDA cache after each batch
- Add memory monitoring
- Optimize tensor allocation

Fixes #456
```

### Python Styleguide

* **Follow PEP 8** - Use Black for automatic formatting
* **Use type hints** - Add type annotations to function parameters and return values
* **Write docstrings** - Use Google or NumPy style docstrings
* **Keep functions small** - Aim for functions under 50 lines
* **Use descriptive names** - Variables and functions should be self-documenting

**Good example:**
```python
def detect_objects(
    image: np.ndarray,
    model_path: str,
    confidence_threshold: float = 0.25,
    iou_threshold: float = 0.45
) -> List[Detection]:
    """
    Detect objects in an image using YOLOv13.
    
    Args:
        image: Input image as numpy array (H, W, C)
        model_path: Path to YOLOv13 model file
        confidence_threshold: Minimum confidence for detections
        iou_threshold: IoU threshold for NMS
        
    Returns:
        List of Detection objects with bounding boxes and scores
        
    Raises:
        ValueError: If model_path doesn't exist
        RuntimeError: If CUDA is not available for GPU inference
    """
    if not os.path.exists(model_path):
        raise ValueError(f"Model not found: {model_path}")
    
    # Implementation here...
```

### Documentation Styleguide

* **Use clear, concise language**
* **Include code examples** for all functions
* **Add screenshots or GIFs** for UI features
* **Keep it up to date** with code changes
* **Use consistent formatting** and structure

## 📝 Additional Notes

### Issue and Pull Request Labels

This section lists the labels we use to help us track and manage issues and pull requests.

* **bug** - Something isn't working
* **documentation** - Improvements or additions to documentation
* **enhancement** - New feature or request
* **good first issue** - Good for newcomers
* **help wanted** - Extra attention is needed
* **invalid** - Something seems wrong or unrelated
* **question** - Further information is requested
* **wontfix** - This will not be worked on

### Development Setup

1. **Fork and clone** the repository
2. **Create a virtual environment**:
   ```bash
   python -m venv venv
   source venv/bin/activate  # On Windows: venv\Scripts\activate
   ```
3. **Install development dependencies**:
   ```bash
   pip install -r requirements-dev.txt
   ```
4. **Install pre-commit hooks**:
   ```bash
   pre-commit install
   ```
5. **Make your changes** and test them
6. **Submit a pull request**

### Getting Help

If you need help with your contribution:

* **Check existing issues** for similar problems
* **Ask in GitHub Discussions** for general questions
* **Join our Discord** for real-time help
* **Tag maintainers** in issues for urgent matters

## 🎉 Recognition

Contributors are recognized in several ways:

* **Contributors list** in the README
* **Release notes** for significant contributions
* **Special thanks** in documentation
* **Contributor badges** on your profile

## 📞 Contact

If you have any questions about contributing, feel free to reach out:

* **Email**: [your-email@example.com](mailto:your-email@example.com)
* **Discord**: [Join our server](https://discord.gg/your-server)
* **GitHub**: [Open an issue](https://github.com/yourusername/yolov13-detection-suite/issues)

---

**Thank you for contributing to YOLOv13 Live Detection Suite! 🚀**

Your contributions help make computer vision accessible to everyone.
