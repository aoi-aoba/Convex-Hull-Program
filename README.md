# OpenGL Convex Hull Tool

OpenGL 4.1 Core 및 ImGui를 사용한 볼록 껍질(Convex Hull) 알고리즘 시각화 도구입니다.
A visualization tool for the Convex Hull algorithm using OpenGL 4.1 Core and ImGui.

<img width="900" height="600" alt="image" src="https://github.com/user-attachments/assets/25e5bb05-74c4-42d5-9fd6-f68bf78f6735" />

---

## 🌐 Language
- [Korean](#korean)
- [English](#english)

---

<a name="korean"></a>
## 🇰🇷 한국어 (Korean)

### 🚀 사용 방법
프로그램을 실행한 후, 우측의 **통합 컨트롤 패널(Control Panel)**을 통해 알고리즘을 테스트할 수 있습니다.

#### 1. 점(Points) 생성 및 관리
- **마우스 클릭**: 화면의 빈 공간을 클릭하여 점을 추가합니다. (상/하단 바 영역 제외)
- **랜덤 생성**: `Seed`와 `Count`를 설정한 후 `Make it!`을 클릭합니다.
- **좌표 직접 입력**: 하단의 `Add Point By Pixel Range` 섹션에서 원하는 픽셀 좌표(X, Y)를 입력하여 정교하게 점을 추가할 수 있습니다. (범위 초과 시 경고 팝업 노출)
- **전체 삭제**: `Erase All` 버튼으로 모든 데이터를 초기화합니다.

#### 2. 스타일 커스터마이징
- **Visual Styles**: 점의 크기와 색상, 볼록 껍질 선의 굵기와 색상, 배경색을 실시간으로 조절할 수 있습니다.

#### 3. Convex Hull 계산 및 I/O
- **계산**: 하단 바의 **`Get Convex Hull`** 버튼을 클릭하면 Graham Scan 알고리즘이 작동합니다.
- **데이터 관리**: 상단 바의 `Import/Export` 버튼을 통해 점 데이터를 `points.csv` 파일로 저장하거나 불러올 수 있습니다.

#### ⚠️ 실행 시 주의사항
- **셰이더 경로**: 실행 파일(`.exe`)과 같은 위치에 `shaders` 폴더가 있어야 합니다.
- **입력 범위**: 직접 입력 시 상단 바(40px) 및 하단 바(70px) 영역을 제외한 가시 영역 내의 좌표만 유효합니다.

---

<a name="english"></a>
## 🇺🇸 English

### 🚀 Usage
Use the **Unified Control Panel** on the right to interact with the algorithm.

#### 1. Point Creation & Management
- **Mouse Click**: Left-click on empty space to add points (excluding UI bar areas).
- **Random Generation**: Set `Seed` and `Count`, then click `Make it!`.
- **Manual Input**: Use the `Add Point By Pixel Range` section to add points at specific pixel coordinates. A warning popup will appear if the input is out of bounds.
- **Clear All**: Reset everything using the `Erase All` button.

#### 2. Style Customization
- **Visual Styles**: Real-time adjustment of point size/color, hull line width/color, and background color.

#### 3. Convex Hull & I/O
- **Calculate**: Click **`Get Convex Hull`** on the bottom bar to run the Graham Scan algorithm.
- **Data I/O**: Use `Import/Export` buttons on the top bar to manage point data via `points.csv`.

#### ⚠️ Troubleshooting
- **Shader Path**: Ensure the `shaders` folder is in the same directory as the executable (`.exe`).
- **Input Clamping**: Manual coordinates must be within the visible canvas (excluding 40px TopBar and 70px BottomBar).

---

## ✨ Key Features
- **Graham Scan Algorithm**: Efficient calculation of the smallest convex polygon.
- **Unified UI**: Grouped settings for point management, styles, and manual input.
- **Real-time Feedback**: Instant rendering of color, size, and coordinate changes.
- **Validation System**: Modal popups for out-of-range coordinate inputs.

## 🛠 Development Environment
- **Language**: C++ / OpenGL 4.1 Core
- **Libraries**: GLEW, GLFW, ImGui
- **Dependency Manager**: vcpkg (Manifest Mode)
