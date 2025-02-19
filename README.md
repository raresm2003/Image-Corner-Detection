# 🖼️ Image Corner Detection

This project implements **corner detection** in grayscale images using the **Shi-Tomasi algorithm**. It compares two approaches:
- **Standard OpenCV implementation** (`goodFeaturesToTrack`)
- **Custom implementation of Shi-Tomasi**

## 📌 Project Overview

The goal of this project is to detect key points (corners) in grayscale images, which are useful in **object recognition, tracking, and feature extraction**.

### 🔹 Features Implemented:
- Load images in **grayscale**.
- Detect corners using:
  - **OpenCV’s** `goodFeaturesToTrack` function.
  - **Custom Shi-Tomasi implementation**.
- Display results:
  - Original image.
  - Image with detected corners using **OpenCV**.
  - Image with detected corners using **custom implementation**.

## 🏗️ System Architecture

### 🛠️ Modules Implemented:
1️⃣ **Image Loading:** Loads the image from disk in grayscale.  
2️⃣ **Shi-Tomasi (OpenCV):** Uses `goodFeaturesToTrack` with parameters like:
   - `maxCorners`, `qualityLevel`, `minDistance`, `blockSize`, `useHarrisDetector`, `k`  
3️⃣ **Shi-Tomasi (Custom):** 
   - Computes image derivatives using **Sobel operator**.
   - Constructs **structure matrix** (Ixx, Iyy, Ixy).
   - Computes eigenvalues to determine corner strength.
   - Filters detected corners based on **threshold & minimum distance**.
4️⃣ **Result Visualization:** Displays detected corners.

## 🛠️ Technologies Used

| Component          | Technology |
|--------------------|------------|
| Programming Language | Python |
| Image Processing   | OpenCV |
| UI & Visualization | Matplotlib |

## ▶️ Running the Project

1️⃣ **Clone the repository:**
   ```sh
   git clone https://github.com/raresm2003/Image-Corner-Detection.git
   cd image-corner-detection
   ```

2️⃣ **Run the application**

## 🚀 Future Improvements

- Extend implementation to **Harris Corner Detector**.
- Add **real-time video corner detection**.
- Improve UI for parameter tuning.

## 👨‍💻 Contributors

**[Miclea Rareș](https://github.com/raresm2003)**  

---

### ⭐ If you like this project, give it a star! ⭐  

