//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include <VertexTypes.h>
#include <PrimitiveBatch.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include <Keyboard.h>

#include "DebugCamera.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:
	using Matrix = DirectX::SimpleMath::Matrix;

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;
	
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;


	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//デバック用
	std::unique_ptr<DebugCamera> m_debugCamera;

	//エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> m_factory;

	//地面モデル
	std::unique_ptr<DirectX::Model> m_modelGround;

	//ティーポットモデル
	/*std::unique_ptr<DirectX::Model> m_teapot;
	DirectX::SimpleMath::Matrix m_worldTeapot[20];
	Matrix m_transmat[20];
	int m_ro;*/

	//頭
	std::unique_ptr<DirectX::Model> m_hed;

	//地面ワールド行列
	//DirectX::SimpleMath::Matrix m_worldGround[100 * 100];

	////天球モデル
	std::unique_ptr<DirectX::Model> m_modelSkydorme;


	////半球モデル
	//std::unique_ptr<DirectX::Model> m_hemisphere;

	////半球ワールド行列
	//int m_worldHemisphereNam;
	//DirectX::SimpleMath::Matrix m_worldHemisphere[20];

	//スケール
	//Matrix scalemat[20];
	//回転行列
	//ロール
	//Matrix rotmatZ[20];
	//ビッチ()
	//Matrix rotmatX[20];
	//ヨー(方位角)
	//Matrix rotmatY[20];
	//回転行列の計算
	//Matrix rotmat[20];
	//平行移動
	//Matrix transmat[20];
	//回る
	//float m_mawaru;

	//キーボード
	std::unique_ptr<DirectX::Keyboard> keyboard;

	//自機の座標
	DirectX::SimpleMath::Vector3 tank_pos;
	//自機の回転
	float tank_angl;
	//自機のワールド行列
	Matrix tank_world;
};