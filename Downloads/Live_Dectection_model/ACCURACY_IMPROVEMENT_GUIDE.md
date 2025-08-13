# 🎯 YOLOv13 Detection Accuracy Improvement Guide

This guide provides comprehensive strategies to improve the detection accuracy of your YOLOv13 model.

## 🚀 Quick Start - Immediate Improvements

### 1. Use Larger Models
```bash
# Download better models
python download_models.py --model small    # Better than nano
python download_models.py --model medium   # Higher accuracy
python download_models.py --model large    # Maximum accuracy

# Run with better model
python webcam_detection_enhanced.py --models yolov13s.pt yolov13m.pt
```

### 2. Optimize Detection Parameters
```bash
# Lower confidence threshold for more detections
python webcam_detection_enhanced.py --conf 0.25 --iou 0.45

# Use ensemble detection
python webcam_detection_enhanced.py --models yolov13n.pt yolov13s.pt --ensemble wbf
```

## 📊 Model Size vs Accuracy Trade-offs

| Model | Size | Speed | Accuracy | Use Case |
|-------|------|-------|----------|----------|
| **yolov13n.pt** | 6.7 MB | ⚡ Fast | 🟡 Low | Real-time, edge devices |
| **yolov13s.pt** | 22.6 MB | 🟡 Medium | 🟢 Medium | Balanced applications |
| **yolov13m.pt** | 52.4 MB | 🟠 Slow | 🟢 High | High accuracy needed |
| **yolov13l.pt** | 87.7 MB | 🔴 Slow | 🔵 Very High | Maximum accuracy |
| **yolov13x.pt** | 136.7 MB | 🔴 Slowest | 🔵 Highest | Research, best results |

## 🎯 Advanced Accuracy Techniques

### 1. Ensemble Detection
Combine multiple models for better accuracy:

```python
# Use multiple models together
detector = EnhancedWebcamDetector(
    model_paths=['yolov13n.pt', 'yolov13s.pt', 'yolov13m.pt'],
    ensemble_method='wbf'  # Weighted Boxes Fusion
)
```

**Benefits:**
- Reduces false negatives
- Improves detection confidence
- Better handling of edge cases

### 2. Test Time Augmentation (TTA)
Enable during inference for better accuracy:

```python
# In the enhanced detector
results = model(frame, 
               augment=True,  # Enable TTA
               conf=0.25,
               iou=0.45)
```

**TTA Techniques:**
- Scale variations (0.9x, 1.0x, 1.1x)
- Horizontal flipping
- Brightness/contrast adjustments

### 3. Optimized Preprocessing
```python
# Frame preprocessing for better detection
def _preprocess_frame(self, frame):
    # Resize to optimal input size
    target_size = (640, 640)  # or (832, 832) for higher accuracy
    
    # Maintain aspect ratio with padding
    h, w = frame.shape[:2]
    scale = min(target_size[0] / w, target_size[1] / h)
    new_w, new_h = int(w * scale), int(h * scale)
    
    # High-quality interpolation
    resized = cv2.resize(frame, (new_w, new_h), 
                        interpolation=cv2.INTER_LINEAR)
    
    return resized
```

### 4. Parameter Tuning

#### Confidence Threshold
- **Lower (0.1-0.3)**: More detections, potential false positives
- **Medium (0.3-0.5)**: Balanced approach
- **Higher (0.5-0.9)**: Fewer detections, higher confidence

#### IoU Threshold
- **Lower (0.3-0.4)**: More aggressive duplicate removal
- **Medium (0.4-0.5)**: Balanced approach
- **Higher (0.5-0.7)**: Less aggressive filtering

#### Class-Agnostic NMS
```python
model.agnostic_nms = True  # Better for overlapping objects
```

## 🔧 Hardware Optimizations

### GPU Acceleration
```python
# Enable TensorRT optimizations
if torch.cuda.is_available():
    torch.backends.cuda.matmul.allow_tf32 = True
    torch.backends.cudnn.allow_tf32 = True
    torch.backends.cudnn.benchmark = True
```

### Memory Management
```python
# Optimize GPU memory usage
torch.cuda.empty_cache()  # Clear GPU memory
model.max_det = 100       # Limit detections per frame
```

## 📸 Camera and Input Quality

### Camera Settings
```python
# Optimize camera parameters
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)
cap.set(cv2.CAP_PROP_FPS, 30)
cap.set(cv2.CAP_PROP_AUTOFOCUS, 1)
```

### Image Enhancement
```python
# Apply image enhancement
def enhance_frame(frame):
    # Auto contrast
    lab = cv2.cvtColor(frame, cv2.COLOR_BGR2LAB)
    l, a, b = cv2.split(lab)
    clahe = cv2.createCLAHE(clipLimit=3.0, tileGridSize=(8,8))
    cl = clahe.apply(l)
    enhanced = cv2.merge((cl,a,b))
    return cv2.cvtColor(enhanced, cv2.COLOR_LAB2BGR)
```

## 🎛️ Configuration-Based Tuning

Use the `accuracy_config.yaml` file for easy parameter adjustment:

```yaml
# Detection Parameters
detection:
  confidence_threshold: 0.25    # Adjust based on your needs
  iou_threshold: 0.45          # NMS aggressiveness
  
# Preprocessing
preprocessing:
  input_size: [832, 832]       # Larger size = better accuracy
  tta_enabled: true            # Enable test time augmentation
  
# Performance
performance:
  enable_tensorrt: true        # GPU optimization
  enable_fp16: true            # Half-precision for speed
```

## 📈 Performance Monitoring

### Real-time Metrics
```python
# Monitor detection performance
cv2.putText(frame, f"FPS: {fps:.1f}", (10, 30), 
           cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
cv2.putText(frame, f"Detections: {len(results)}", (10, 70), 
           cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
cv2.putText(frame, f"Inference: {inference_time*1000:.1f}ms", (10, 110), 
           cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
```

### Accuracy Metrics
- **Precision**: True positives / (True positives + False positives)
- **Recall**: True positives / (True positives + False negatives)
- **F1-Score**: Harmonic mean of precision and recall

## 🎯 Use Case-Specific Optimizations

### Person Detection
```python
# Lower confidence for people
class_thresholds = {'person': 0.2}
# Enable temporal filtering for smooth tracking
temporal_filtering = True
```

### Vehicle Detection
```python
# Higher confidence for vehicles
class_thresholds = {'car': 0.4, 'truck': 0.5}
# Use larger input size for small vehicles
input_size = [832, 832]
```

### Small Object Detection
```python
# Increase input resolution
input_size = [1024, 1024]
# Lower confidence threshold
confidence_threshold = 0.2
# Enable multi-scale detection
multi_scale = True
```

## 🔍 Troubleshooting Common Issues

### Low Detection Rate
1. **Lower confidence threshold**: `--conf 0.2`
2. **Use larger model**: Download `yolov13s.pt` or larger
3. **Enable TTA**: Set `augment=True`
4. **Check lighting**: Ensure good illumination

### High False Positives
1. **Increase confidence threshold**: `--conf 0.5`
2. **Adjust IoU threshold**: `--iou 0.6`
3. **Use ensemble detection**: Combine multiple models
4. **Enable class filtering**: Focus on specific classes

### Slow Performance
1. **Use smaller model**: Switch to `yolov13n.pt`
2. **Enable GPU acceleration**: Ensure CUDA is available
3. **Reduce input size**: Use `(640, 640)` instead of `(1024, 1024)`
4. **Disable TTA**: Set `augment=False`

## 📚 Advanced Techniques

### 1. Custom Training
```bash
# Train on your specific dataset
yolo train model=yolov13n.pt data=custom_data.yaml epochs=100
```

### 2. Transfer Learning
```python
# Fine-tune pre-trained model
model = YOLO('yolov13n.pt')
model.train(data='custom_data.yaml', epochs=50, imgsz=640)
```

### 3. Model Quantization
```python
# INT8 quantization for faster inference
model.export(format='onnx', int8=True)
```

## 🎉 Quick Commands Reference

```bash
# Basic accuracy improvement
python webcam_detection_enhanced.py --models yolov13s.pt --conf 0.25

# Ensemble detection
python webcam_detection_enhanced.py --models yolov13n.pt yolov13s.pt --ensemble wbf

# High accuracy mode
python webcam_detection_enhanced.py --models yolov13m.pt --conf 0.2 --iou 0.4

# Download better models
python download_models.py --model small
python download_models.py --model medium
python download_models.py --info

# Show configuration options
cat accuracy_config.yaml
```

## 📊 Expected Accuracy Improvements

| Technique | Accuracy Gain | Speed Impact | Implementation |
|-----------|---------------|--------------|----------------|
| **Model Size** | +15-25% | -20-40% | Download larger models |
| **Ensemble** | +10-20% | -30-50% | Use multiple models |
| **TTA** | +5-15% | -20-30% | Enable augmentation |
| **Preprocessing** | +5-10% | -5-10% | Optimize input |
| **Parameter Tuning** | +5-15% | Minimal | Adjust conf/iou |
| **Hardware** | +10-20% | +50-100% | GPU optimization |

## 🎯 Best Practices Summary

1. **Start with larger models** for better accuracy
2. **Use ensemble detection** when possible
3. **Enable TTA** for inference-time improvements
4. **Optimize parameters** based on your use case
5. **Monitor performance** in real-time
6. **Use appropriate input sizes** for your objects
7. **Enable GPU acceleration** for better speed
8. **Regularly update models** to latest versions

## 🆘 Getting Help

- Check the configuration file: `accuracy_config.yaml`
- Use the enhanced detection script: `webcam_detection_enhanced.py`
- Download better models: `download_models.py`
- Monitor performance metrics in real-time
- Adjust parameters based on your specific needs

Remember: **Accuracy and speed are trade-offs**. Choose the right balance for your application!
