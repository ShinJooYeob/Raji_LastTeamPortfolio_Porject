#pragma once


enum UPGRADEID
{
	Upgrade_Vopal, Upgrade_PaperGrinder, Upgrade_Horse, Upgrade_Teapot, Upgrade_End
};

enum SCENEID
{
	SCENE_STATIC,
	SCENE_LOBY,
	SCENE_LOADING,
	SCENE_STAGESELECT,
	SCENE_STAGE1,
	SCENE_STAGE2,
	SCENE_STAGE3,
	SCENE_STAGE4,
	SCENE_STAGE5,
	SCENE_STAGE6,
	SCENE_STAGE7,
	SCENE_BOSS,
	SCENE_ENDING,

	SCENE_EDIT,
	SCENE_END
};



enum OBJECTPROTOTYPEID
{
	Prototype_Camera_Main,
	Prototype_Player,

	Prototype_SkyBox,

	Prototype_UIImage,

	Prototype_EditorCursor,
	Prototype_Rect,
	Prototype_Cube,
	Prototype_Terrain,


	Prototype_StaticMapObject,


	Prototype_TestObject,
	Prototype_TestObject2,

	Object_Prototype_End
};



static const _tchar* Tag_Object_Prototype(OBJECTPROTOTYPEID eTag)
{
	switch (eTag)
	{


	case Prototype_Camera_Main:
		return TEXT("Prototype_Camera_Main");
		break;
	case Prototype_SkyBox:
		return TEXT("Prototype_SkyBox");
		break;
	case Prototype_EditorCursor:
		return TEXT("Prototype_EditorCursor");
		break;
	case Prototype_UIImage:
		return TEXT("Prototype_UI_Image");
		break;


	case Prototype_Rect:
		return TEXT("Prototype_Rect");
		break;
	case Prototype_Cube:
		return TEXT("Prototype_Cube");
		break;
	case Prototype_Terrain:
		return TEXT("Prototype_Terrain");
		break;
	case Prototype_Player:
		return TEXT("Prototype_Player");
		break;
		

	case Prototype_StaticMapObject:
		return TEXT("Prototype_StaticMapObject");
		break;
		//////////////////////////////////////////////////////////////////////////

	case Prototype_TestObject:
		return TEXT("Prototype_TestObject");

	case Prototype_TestObject2:
		return TEXT("Prototype_TestObject2");
		
	default:
		MSGBOX("Wrong Type Object Prototype");
		return nullptr;
		break;
	}


}
#define  TAG_OP Tag_Object_Prototype

//
//enum MESHTYPEID
//{
//	Mesh_None,
//	Mesh_Player,
//	Mesh_Monster,
//
//
//
//	Mesh_AlgaeRock_Ledge,
//	Mesh_AlgaeRock_Pillar,
//	Mesh_AlgaeRock_Wall,
//
//	MeshID_End
//};
//
//
//
//static const _tchar* Tag_MeshID(MESHTYPEID eTag)
//{
//	switch (eTag)
//	{
//	case Mesh_None:
//		return TEXT("Mesh_None");
//		break;
//
//	case Mesh_Monster:
//		return TEXT("Monster");
//		break;
//	case Mesh_Player:
//		return TEXT("Player");
//		break;
//
//
//
//
//
//
//
//
//		//////////////////////////////////////////////////////////////////////////
//	case Mesh_AlgaeRock_Ledge:
//		return TEXT("Mesh_AlgaeRock_Ledge");
//		break;
//	case Mesh_TestMesh2:
//		return TEXT("TestMesh2");
//		break;
//	case Mesh_TestMesh3:
//		return TEXT("TestMesh3");
//		break;
//	case Mesh_TestMesh4:
//		return TEXT("TestMesh4");
//		break;
//
//	default:
//		MSGBOX("Wrong Type Mesh");
//		return nullptr;
//		break;
//	}
//
//
//}
//#define  TAG_MESH Tag_MeshID

enum LAYERID
{
	Layer_Camera_Main,
	Layer_Camera_Editor,
	Layer_ScreenEffect,
	Layer_SkyBox,
	Layer_Player,
	Layer_Bullet,
	Layer_ClockBomb,

	Layer_Monster,
	Layer_MonsterBullet,
	Layer_MonsterBullet1,
	Layer_MonsterBullet2,
	Layer_Particle,

	Layer_Terrain,
	Layer_WireTerrain,


	Layer_JumpPad,
	Layer_SteamPad,
	Layer_HiddenPad,
	Layer_TeethObj,
	Layer_RoseObj,
	Layer_Breakable,
	Layer_BreakablePiece,
	Layer_SlideObj,

	Layer_EscalatorPad,
	Layer_ButtonPad,
	Layer_ShrinkFlower,
	Layer_Vent,
	Layer_MazeDoor,
	Layer_ShapeMemoryPad,
	Layer_Presser,



	Layer_StaticMapObj,
	Layer_TriggerCollider,


	Layer_UI_GamePlay,
	Layer_NPC,



	Layer_UI_IMG,
	Layer_UI_BTN,
	Layer_UI_SLIDE,
	Layer_UI_INPUT,

	Layer_TestObject,

};

static const _tchar* Tag_Layer(LAYERID eTag)
{
	switch (eTag)
	{
		
	case Layer_NPC:
		return TEXT("Layer_NPC");
		break;

	case Layer_Camera_Main:
		return TEXT("Layer_Camera_Main");
		break;
	case Layer_Camera_Editor:
		return TEXT("Layer_Camera_Editor");
		break;
	case Layer_ScreenEffect:
		return TEXT("Layer_ScreenEffect");
		break;
	case Layer_TriggerCollider:
		return TEXT("Layer_TriggerCollider");
		break;
		
		

	case Layer_Bullet:
		return TEXT("Layer_Bullet");
		break;
	case Layer_SkyBox:
		return TEXT("Layer_SkyBox");
		break;
	case Layer_Terrain:
		return TEXT("Layer_Terrain");
		break;
	case Layer_WireTerrain:
		return TEXT("Layer_WireTerrain");
		break;
	case Layer_Particle:
		return TEXT("Layer_Particle");
		break;
	case Layer_ClockBomb:
		return TEXT("Layer_ClockBomb");
		break;
		

	case Layer_Monster:
		return TEXT("Layer_Monster");
		break;

	case Layer_MonsterBullet:
		return TEXT("Layer_MonsterBullet");
		break;
	case Layer_MonsterBullet1:
		return TEXT("Layer_MonsterBullet1");
		break;
	case Layer_MonsterBullet2:
		return TEXT("Layer_MonsterBullet2");
		break;


	case Layer_Player:
		return TEXT("Layer_Player");
		break;
	case Layer_JumpPad:
		return TEXT("Layer_JumpPad");
		break;
	case Layer_SteamPad:
		return TEXT("Layer_SteamPad");
		break;
	case Layer_HiddenPad:
		return TEXT("Layer_HiddenPad");
		break;
	case Layer_TeethObj:
		return TEXT("Layer_TeethObj");
		break;
	case Layer_RoseObj:
		return TEXT("Layer_RoseObj");
		break;
	case Layer_Breakable:
		return TEXT("Layer_Breakable");
		break;
	case Layer_BreakablePiece:
		return TEXT("Layer_BreakablePiece");
		break;
	case Layer_SlideObj:
		return TEXT("Layer_SlideObj");
		break;
	case Layer_EscalatorPad:
		return TEXT("Layer_EscalatorPad");
		break;
	case Layer_ButtonPad:
		return TEXT("Layer_ButtonPad");
		break;
	case Layer_ShrinkFlower:
		return TEXT("Layer_ShrinkFlower");
		break;
	case Layer_Vent:
		return TEXT("Layer_Vent");
		break;
	case Layer_MazeDoor:
		return TEXT("Layer_MazeDoor");
		break;
	case Layer_ShapeMemoryPad:
		return TEXT("Layer_ShapeMemoryPad");
		break;
	case Layer_Presser:
		return TEXT("Layer_Presser");
		break;




	case Layer_StaticMapObj:
		return TEXT("Layer_StaticMapObj");
		break;

	case Layer_UI_GamePlay:
		return TEXT("Layer_UI_GamePlay");
		break;

	case Layer_UI_IMG:
		return TEXT("Layer_UI_IMG");
		break;
	case Layer_UI_BTN:
		return TEXT("Layer_UI_BTN");
		break;
	case Layer_UI_SLIDE:
		return TEXT("Layer_UI_SLIDE");
		break;
	case Layer_UI_INPUT:
		return TEXT("Layer_UI_INPUT");
		break;

		//////////////////////////////////////////////////////////////////////////

	case Layer_TestObject:
		return TEXT("Layer_TestObject");
		break;
		
	default:
		MSGBOX("Wrong Type Layer");
		return nullptr;
		break;
	}


}
#define  TAG_LAY Tag_Layer

enum COMPONENTPROTOTYPEID
{
	/////////////////�⺻ ������Ʈ
	Prototype_Renderer,
	Prototype_Transform,
	Prototype_Collider,
	Prototype_Trail,
	Prototype_Shader_VT,
	Prototype_Shader_VCT,
	Prototype_Shader_VNT,
	Prototype_Shader_VNCT,
	Prototype_Shader_VAM,
	Prototype_Shader_VNAM,
	Prototype_Shader_VTXPOINTINST,

	//////////////����////////////////////////////////////////////////////////////
	Prototype_VIBuffer_Rect,
	Prototype_VIBuffer_Cube,
	Prototype_VIBuffer_Terrain,
	Prototype_VIBuffer_Terrain_Edit,
	Prototype_VIBuffer_Point_Instance,

	//////StaticMesh////////////////////////////////////////////////////////////////////

	Prototype_Mesh_None,
	Prototype_Mesh_AlgaeRock_Ledge,


	//////���̳���Mesh////////////////////////////////////////////////////////////////////

	Prototype_Mesh_Player,


	Prototype_Mesh_SkyBox,


	Prototype_Mesh_TestObject,
	/////////�ؽ���/////////////////////////////////////////////////////////////////
	Prototype_Texture_Player,
	Prototype_Texture_SkyBox,
	Prototype_Texture_EditScene,
	Prototype_Texture_Terrain,
	Prototype_Texture_Edit_Terrain,
	Prototype_Texture_DefaultUI,
	Prototype_Texture_InstanceParticleTex,
	Prototype_Texture_ScreenEffectUI,
	Prototype_Texture_PlayerEffect,
	Prototype_Texture_DissolveEffect,
	Prototype_Texture_GamePlayScene,
	Prototype_Texture_LoadingScene,
	Prototype_Texture_LobyScene,
	Prototype_Texture_SettingScene,
	Prototype_Texture_MskTex,
	Prototype_Texture_PauseUI,


};
static const _tchar* Tag_Component_Prototype(COMPONENTPROTOTYPEID eTag)
{
	switch (eTag)
	{

	case Prototype_Renderer:
		return TEXT("Prototype_Component_Renderer");
		break;
	case Prototype_Transform:
		return TEXT("Prototype_Component_Transform");
		break;
	case Prototype_Collider:
		return TEXT("Prototype_Component_Collider");
		break;
	case Prototype_Trail:
		return TEXT("Prototype_Component_Trail");
		break;

	case Prototype_Shader_VT:
		return TEXT("Prototype_Component_Shader_VTXTEX");
		break;
	case Prototype_Shader_VCT:
		return TEXT("Prototype_Component_Shader_VTXCUBETEX");
		break;

	case Prototype_Shader_VNT:
		return TEXT("Prototype_Component_Shader_VTXNORMTEX");
		break;

	case Prototype_Shader_VNCT:
		return TEXT("Prototype_Component_Shader_VTXNORMCUBETEX");
		break;
	case Prototype_Shader_VAM:
		return TEXT("Prototype_Component_Shader_VTXANIMMODEL");
		break;
	case Prototype_Shader_VNAM:
		return TEXT("Prototype_Component_Shader_VTXNONANIMMODEL");
		break;
	case Prototype_Shader_VTXPOINTINST:
		return TEXT("Prototype_Component_Shader_VTXPOINTINST");
		break;


	case Prototype_VIBuffer_Rect:
		return TEXT("Prototype_Component_VIBuffer_Rect");
		break;

	case Prototype_VIBuffer_Cube:
		return TEXT("Prototype_Component_VIBuffer_Cube");
		break;

	case Prototype_VIBuffer_Point_Instance:
		return TEXT("Prototype_VIBuffer_Point_Instance");
		break;
		

		//�޽�////////////////////////////////////////////////////////////////////////

	case Prototype_Mesh_None:
		return TEXT("Prototype_Mesh_None");
		break;
	case Prototype_Mesh_AlgaeRock_Ledge:
		return TEXT("Prototype_Mesh_AlgaeRock_Ledge");
		break;
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		

	case Prototype_Mesh_Player:
		return TEXT("Prototype_Mesh_Player");
		break;

	case Prototype_Mesh_TestObject:
		return TEXT("Prototype_Mesh_TestObject");
		break;
	case Prototype_Mesh_SkyBox:
		return TEXT("Prototype_Mesh_SkyBox");
		break;


		/////////////////�ؽ�ó////////////////////////////////////////////////////////


	case Prototype_Texture_Player:
		return TEXT("Prototype_Component_Texture_Player");
		break;
	case Prototype_Texture_PlayerEffect:
		return TEXT("Prototype_Texture_PlayerEffect");
		break;
	case Prototype_Texture_DissolveEffect:
		return TEXT("Prototype_Texture_DissolveEffect");
		break;
	case Prototype_Texture_ScreenEffectUI:
		return TEXT("Prototype_Texture_ScreenEffectUI");
		break;
		
	case Prototype_Texture_SkyBox:
		return TEXT("Prototype_Component_Texture_SkyBox");
		break;

	case Prototype_Texture_EditScene:
		return TEXT("Prototype_Component_Texture_EditScene");

		break;
	case 	Prototype_Texture_Terrain:
		return TEXT("Prototype_Component_Texture_Terrain");

		break;
	case 	Prototype_Texture_Edit_Terrain:
		return TEXT("Prototype_Texture_Edit_Terrain");

	case 	Prototype_Texture_DefaultUI:
		return TEXT("Prototype_Texture_DefaultUI");
		break;


	case 	Prototype_Texture_GamePlayScene:
		return TEXT("Prototype_Texture_GamePlayScene");
		break;

	case 	Prototype_Texture_LoadingScene:
		return TEXT("Prototype_Texture_LoadingScene");
		break;

	case 	Prototype_Texture_LobyScene:
		return TEXT("Prototype_Texture_LobyScene");
		break;

		case
			Prototype_Texture_SettingScene:
				return TEXT("Prototype_Texture_SettingScene");
				break;

		case Prototype_Texture_MskTex:
			return TEXT("Prototype_Texture_MskTex");
			break;
		case Prototype_Texture_InstanceParticleTex:
			return TEXT("Prototype_Texture_InstanceParticleTex");
			break;
		case Prototype_Texture_PauseUI:
			return TEXT("Prototype_Texture_PauseUI");
			break;
			
				//�޽�////////////////////////////////////////////////////////////////////////







				break;
		case 	Prototype_VIBuffer_Terrain:
			return TEXT("Prototype_Component_VIBuffer_Terrain");
			break;
		case 	Prototype_VIBuffer_Terrain_Edit:
			return TEXT("Prototype_Component_VIBuffer_Terrain_Edit");
			break;



			//////////////////////////////////////////////////////////////////////////
		default:
			MSGBOX("Wrong Type Layer");
			return nullptr;
			break;
	}


}

#define  TAG_CP Tag_Component_Prototype

enum COMPONENTID
{
	Com_Renderer,
	Com_VIBuffer,
	Com_Transform,
	Com_SubTransform,
	Com_Texture,
	Com_Inventory,
	Com_Shader,
	Com_ShaderSub,
	Com_Model,
	Com_SubModel,
	Com_Collider,
	Com_SwordTrail,
	Com_SubSwordTrail
};
static const _tchar* Tag_Component(COMPONENTID eTag)
{
	switch (eTag)
	{
	case Com_Renderer:
		return TEXT("Com_Renderer");
		break;
	case Com_VIBuffer:
		return TEXT("Com_VIBuffer");
		break;
	case Com_Transform:
		return TEXT("Com_Transform");
		break;
	case Com_SubTransform:
		return TEXT("Com_SubTransform");
		break;
		
	case Com_Texture:
		return TEXT("Com_Texture");
		break;
	case Com_Inventory:
		return TEXT("Com_Inventory");
		break;
	case Com_Shader:
		return TEXT("Com_Shader");
		break;
	case Com_ShaderSub:
		return TEXT("Com_ShaderSub");
		break;
	case Com_Model:
		return TEXT("Com_Model");
		break;
	case Com_SubModel:
		return TEXT("Com_SubModel");
		break;

	case Com_Collider:
		return TEXT("Com_Collider");
		break;

	case Com_SwordTrail:
		return TEXT("Com_SwordTrail");
		break;
	case Com_SubSwordTrail:
		return TEXT("Com_SubSwordTrail");
		break;
		
		

		//////////////////////////////////////////////////////////////////////////
	default:
		MSGBOX("Wrong Type Component");
		return nullptr;
		break;
	}


}
#define  TAG_COM Tag_Component



static const char* Tag_ModelTextureType(_uint eTag)
{
	switch (eTag)
	{
	case aiTextureType_NONE:		return "None";
		break;
	case aiTextureType_DIFFUSE:	return "g_DiffuseTexture";
		break;
	case aiTextureType_SPECULAR:return "g_SpecularTexture";
		break;
	case aiTextureType_AMBIENT:return "g_AmbientTexture";
		break;
	case aiTextureType_EMISSIVE:return "g_EmissiveTexture";
		break;
	case aiTextureType_HEIGHT:return "g_HeightTexture";
		break;
	case aiTextureType_NORMALS:return "g_NormalTexture";
		break;
	case aiTextureType_SHININESS:return "g_ShininessTexture";
		break;
	case aiTextureType_OPACITY:return "g_OpacityTexture";
		break;
	case aiTextureType_DISPLACEMENT:return "g_DisplaceTexture";
		break;
	case aiTextureType_LIGHTMAP:return "g_LightMapTexture";
		break;
	case aiTextureType_REFLECTION:return "g_ReflectTexture";
		break;
	case aiTextureType_BASE_COLOR:return "g_BaseColorTexture";
		break;
	case aiTextureType_NORMAL_CAMERA:return "g_NormalCamTexture";
		break;
	case aiTextureType_EMISSION_COLOR:return "g_EmissionColorTexture";
		break;
	case aiTextureType_METALNESS:return "g_MetalTexture";
		break;
	case aiTextureType_DIFFUSE_ROUGHNESS:return "g_DiffuseRoughTexture";
		break;
	case aiTextureType_AMBIENT_OCCLUSION:return "g_AmbientOcculusionTexture";
		break;
	case aiTextureType_UNKNOWN:return "";
		break;
	case _aiTextureType_Force32Bit:return "";
		break;
	default:
		OutputDebugStringW(L"Wrong Type Texture");
		__debugbreak();
		return nullptr;
		break;
	}
}

#define  MODLETEXTYPE Tag_ModelTextureType















//
//
//enum EasingTypeID
//{
//	TYPE_Linear = 0,
//
//	TYPE_QuadIn = 1,
//	TYPE_QuadOut,
//	TYPE_QuadInOut,
//
//	TYPE_CubicIn = 4,
//	TYPE_CubicOut,
//	TYPE_CubicInOut,
//
//	TYPE_QuarticIn = 7,
//	TYPE_QuarticOut,
//	TYPE_QuarticInOut,
//
//	TYPE_QuinticIn = 10,
//	TYPE_QuinticOut,
//	TYPE_QuinticInOut,
//
//	TYPE_SinIn = 13,
//	TYPE_SinOut,
//	TYPE_SinInOut,
//
//	TYPE_ExpoIn = 16,
//	TYPE_ExpoOut,
//	TYPE_ExpoInOut,
//
//	TYPE_CircularIn = 19,
//	TYPE_CircularOut,
//	TYPE_CircularInOut,
//
//	TYPE_ElasticIn = 22,
//	TYPE_ElasticOut,
//	TYPE_ElasticInOut,
//
//	TYPE_BounceIn = 25,
//	TYPE_BounceOut,
//
//
//	TYPE_End
//};

