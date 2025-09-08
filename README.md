# FdF

## 1️⃣ 프로젝트 소개

FdF는 42서울 커리큘럼의 그래픽스 프로젝트로, Wireframe 방식으로 3D 지형 데이터를 2D 화면에 렌더링하는 프로그램을 구현하는 과제입니다. minilibx라는 경량 그래픽스 라이브러리를 사용하여 OpenGL 등 고수준 프레임워크 없이, 저수준 그래픽스 API 호출만으로 화면에 선을 그려 지형을 표현합니다. Bonus 구현까지 완료하여 단순 렌더링을 넘어 다양한 상호작용 기능과 시각적 효과를 추가했습니다.

---

## 2️⃣ 과제 목표
	•	isometric projection (등각 투영)을 이해하고, 3차원 좌표 데이터를 2차원 화면에 올바르게 변환하기.
	•	Bresenham 알고리즘을 사용해 픽셀 단위로 직선을 그리며, 고정 소수점 기반 계산으로 효율적 렌더링을 구현.
	•	이벤트 처리(keyboard, mouse)를 통해 사용자가 직접 시점을 이동/확대/축소할 수 있는 인터랙티브 뷰어를 제작.
	•	보너스에서는 색상, 회전, 마우스 조작 등 기능을 확장하여 실제 그래픽스 뷰어에 가까운 완성도를 달성하는 것.

---

## 3️⃣ 구현 사항
### * Mandatory
  - map 파일을 파싱하여 고도 데이터(z값)를 2D 배열로 저장.
  - 등각 투영 변환을 적용하여 (x, y, z) → (x’, y’) 좌표 계산.
  - Bresenham 알고리즘으로 선형 보간(line interpolation) 기반의 선분 그리기 구현.
  - 창 크기 내에서 자동으로 지도 크기를 조정(scale & offset).
### * Bonus
  - 색상 그라데이션: 고도 값에 따라 다른 색상을 부여하여 지형의 높낮이가 직관적으로 보이도록 구현.
  - 마우스 인터랙션: 드래그로 시점 이동, 휠로 확대/축소 기능 추가.
  - 키보드 컨트롤: 화살표 키로 카메라 이동, +/- 키로 카메라 이동 속도, C 키로 색상 그라데이션 모드 변환 등 다양한 단축키 지원.
  - 다양한 투영 방식: 등각 투영 외에도 1인칭 시점 투영으로 전환할 수 있도록 구현.
  - 성능 최적화: 큰 맵에서도 빠른 렌더링을 위해 double buffer 방식과 draw 최소화를 적용.

---

## 5️⃣ 배운 점
	•	그래픽스 기초 수학: 벡터 변환, 등각 투영 공식, 선형 보간의 원리를 코드로 직접 구현하며 수학과 프로그래밍의 연결을 체감.
	•	저수준 그래픽스 처리: 라이브러리 도움 없이 픽셀 단위로 선을 그리는 과정을 통해 그래픽스 파이프라인의 원리를 학습.
	•	이벤트 처리 구조: 키보드와 마우스 이벤트를 minilibx 이벤트 루프와 연동하여 실시간 상호작용 시스템을 구축.
	•	코드 최적화 중요성: 큰 데이터셋에서도 매끄럽게 작동하도록 불필요한 연산을 줄이고 캐시 효율을 고려한 구조 설계.

---

## 6️⃣ 사용 방법
bash
```
# 1. 프로젝트 빌드
make        # 기본 빌드
make bonus  # 보너스 기능 포함 빌드

# 2. 실행
./fdf maps/42.fdf        # 지정한 map 파일을 wireframe으로 렌더링
./fdf maps/pyramide.fdf

# 3. 주요 조작
- 마우스 드래그 : 시점 이동
- 마우스 휠    : 줌 인/아웃
- 화살표 키    : 이미지 이동
- wasd 키    : 이미지 회전
- +/- 키     : 카메라 이동속도 증가/감소
- [/] 키     : 카메라 회전속도 증가/감소
- T 키       : 투영 방식 전환 (Isometric <-> 1-point Perpective)
- C 키       : 색상 그라데이션 모드 변환 (픽셀 컬러 <-> 높이 표현)
```

---

## 7️⃣ 사진 예시
<img width="1274" height="1018" alt="스크린샷 2025-08-18 오후 10 35 55" src="https://github.com/user-attachments/assets/cd06aeaf-b169-49fe-8508-e46cda891012" />

<img width="1269" height="1015" alt="스크린샷 2025-08-18 오후 10 36 10" src="https://github.com/user-attachments/assets/713b1833-628e-4398-a628-0754f87c8a90" />

<img width="1271" height="1020" alt="스크린샷 2025-08-18 오후 10 36 51" src="https://github.com/user-attachments/assets/2a9fcbf5-7f51-4969-a4eb-2bc4d46a1efb" />

<img width="1271" height="1021" alt="스크린샷 2025-08-18 오후 10 37 15" src="https://github.com/user-attachments/assets/80ee6f76-62ca-475a-b5ff-20dc1399d8fa" />

---

## 7️⃣ 동작 영상
### pyramide.fdf
https://github.com/user-attachments/assets/83e4dc4e-aa18-4a2e-baa8-f87b53f6d466

### julia.fdf
https://github.com/user-attachments/assets/7a98ecae-f931-48c0-8e42-9b17b0bc451d

---

## 9️⃣ 기술 스택
	•	언어: C
	•	그래픽스 라이브러리: minilibx (X11 기반)
	•	알고리즘: Bresenham’s line algorithm, 선형 보간(gradient), 행렬 변환
	•	개발 환경: Unix/Linux, Makefile 기반 자동 빌드
	•	추가 구현: 이벤트 루프, double buffering, 색상 보간 로직
