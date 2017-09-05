jigok-flood-simulator-opengl
=============
# Notice

본 프로젝트는 포항공과대학교 2016년 봄학기 컴퓨터그래픽스(CSED451) 학기 프로젝트로 제작되었다.

[데모 영상][video]

# Introduction

이 프로젝트의 주제는 ‘지곡회관 홍수 시뮬레이터’이다. 프로젝트의 이름에서부터 알 수 있듯 Modeling과 Texture mapping, 그리고 다양한 shading 기법을 이용하여 지곡회관과 그 주변을 사
을 것이다. 이렇게 만들어낸 지곡회관과 물의 움직임을 바탕으로 하여 지곡회관에 홍수가 난 모습을 시뮬레이션 하는 것이 이 프로젝트의 목표이다.

# Dependencies

	Visual Studio 2017
	freeGLUT 2.8.1
	GLEW 2.0.0

# How to use

솔루션 파일 FluidSimulation.sln 연 후 Ctrl + F5 키를 누르면 시뮬레이션을 실행시킬 수 있다. 이때 fluid simulation을 여려가지로 할 수있는데, 이는 config.h를 조작하므로써 설정을 바꿀 수 있다.

	#define SCENARIO_NARROW

일반적인 물의 시뮬레이션을 볼 수 있다.

	#define SCENARIO_NARROW
	#define SCENARIO_JELLY

점성이 높은 물의 시뮬레이션을 볼 수 있다.

	#define SCENARIO_JIGOK

지곡회관오브젝트를 불러와 지곡회관 홍수 시뮬레이션을 할 수 있다.

# Futher information

자세한 이론적 배경이나 설계, 참고자료는 같이 첨부된 보고서에 적혀있다.

[video]: https://www.facebook.com/ilhwan.hwang.96/videos/1233028630071308/