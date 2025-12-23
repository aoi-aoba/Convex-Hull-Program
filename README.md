# OpenGL Convex Hull Tool

OpenGL 4.1 Core 및 ImGui를 사용한 볼록 껍질(Convex Hull) 알고리즘 시각화 도구입니다.

A visualization tool for the Convex Hull algorithm using OpenGL 4.1 Core and ImGui.

---

## 🌐 Language
- [Korean](#korean)
- [English](#english)

---

<a name="korean"></a>
## 한국어

### 🚀 사용 방법 (Usage)
프로그램을 실행한 후, 다음과 같은 단계를 통해 Convex Hull(볼록 껍질) 알고리즘을 테스트할 수 있습니다.

#### 1. 점(Points) 생성 및 관리
- **직접 추가**: 화면의 빈 공간을 마우스 왼쪽 버튼으로 클릭하여 점을 추가합니다.
- **랜덤 생성**: 우측 상단 `Point Setting` 창에서 Seed 설정 후 `Make it!`을 클릭합니다.
- **전체 삭제**: `Erase All` 버튼을 누르면 모든 데이터가 초기화됩니다.

#### 2. Convex Hull 계산
- 하단 바의 **`Get Convex Hull`** 버튼을 클릭합니다.
- Graham Scan 알고리즘이 작동하여 빨간색 외곽선을 화면에 표시합니다.

#### 3. 데이터 저장 및 불러오기 (I/O)
- **Export**: 현재 점 좌표를 `points.csv`로 저장합니다. (상단 왼쪽 Export 버튼)
- **Import**: `points.csv` 파일로부터 좌표를 읽어와 복원합니다. (상단 왼쪽 Import 버튼)

#### ⚠️ 실행 시 주의사항
- **셰이더 로드 에러**: 실행 시 셰이더 파일을 찾지 못한다면, `shaders` 폴더가 실행 파일(`.exe`)과 같은 경로에 있는지 확인하세요.
- **최소 점 개수**: 계산을 위해서는 최소 **3개 이상**의 점이 필요합니다.

---

<a name="english"></a>
## English
### 🚀 Usage
Follow these steps to test the Convex Hull algorithm after running the program.

#### 1. Point Creation & Management
- **Manual Addition**: Left-click on any empty space on the screen to add a point.
- **Random Generation**: Set the `Scatter Seed` in the `Point Setting` window and click `Make it!`.
- **Clear All**: Click the `Erase All` button to reset all points and the calculated hull.

#### 2. Calculate Convex Hull
- Click the **`Get Convex Hull`** button on the bottom bar.
- The Graham Scan algorithm will execute and display the red boundary on the screen.

#### 3. Data Import/Export (I/O)
- **Export**: Save the current point coordinates to `points.csv`. (Top-left Export button)
- **Import**: Restore coordinates from an existing `points.csv` file. (Top-left Import button)

#### ⚠️ Troubleshooting
- **Shader Load Error**: If you see a shader-related error, ensure the `shaders` folder is in the same directory as the executable (`.exe`).
- **Minimum Points**: At least **3 points** are required to calculate a Convex Hull.

---

## ✨ Features
- **Graham Scan Algorithm**: Efficient calculation of the smallest convex polygon containing all points.
- **Real-time Interaction**: Add points via mouse clicks and generate random seeds.
- **Data Management**: Support for CSV file Import/Export.
- **Modern UI**: Intuitive control panel based on ImGui.

## 🛠 Development Environment (개발 환경)
- **Language**: C++ / OpenGL 4.1 Core
- **Libraries**: GLEW, GLFW, ImGui
- **Dependency Manager**: vcpkg (Manifest Mode)