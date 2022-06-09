#if 0
	***	hlms_uv_count0	2
	***	hlms_pose	0
	***	uv_emissive	0
	***	first_valid_detail_map_nm	4
	***	fresnel_scalar	0
	***	hlms_uv_count	1
	***	pcf_iterations	4
	***	uv_detail_nm1	0
	***	uv_detail_nm2	0
	***	hlms_tex_gather	1
	***	precision_mode	-2126167738
	***	BRDF_Default	1
	***	hlms_shadowmap2_array_idx	0
	***	set0_texture_slot_end	3
	***	uv_specular	0
	***	hlms_shadowmap1_uv_min_x_fract	0
	***	hlms_shadowmap2_uv_min_x_fract	50000
	***	hlms_forwardplus_flipY	1
	***	glsl	635204550
	***	hlms_shadowmap2_uv_max_y_fract	42857
	***	hlms_shadowmap0_uv_max_x_fract	0
	***	hlms_shadowmap2_uv_max_y_int	0
	***	hlms_num_shadow_map_lights	3
	***	hlms_lights_directional	1
	***	hlms_shadowmap0_uv_min_y_fract	0
	***	samplerStateStart	3
	***	hlms_shadowmap1_uv_min_y_fract	28571
	***	alpha_test	0
	***	GGX_height_correlated	1
	***	hlms_shadowmap2	0
	***	hlms_shadowmap0_light_idx	0
	***	glsles	1070293233
	***	metallic_workflow	0
	***	hw_gamma_write	1
	***	hlms_shadowmap0_uv_min_y_int	0
	***	uv_detail_weight	0
	***	hlms_shadowmap0_uv_max_x_int	1
	***	hlms_shadowmap1_uvs_fulltex	1
	***	hlms_alpha_to_coverage	0
	***	cubemaps_as_diffuse_gi	1
	***	hlms_shadowmap1_uv_max_y_fract	42857
	***	uv_detail_nm3	0
	***	hlms_shadowmap2_uv_max_x_int	1
	***	envmap_scale	1
	***	hlms_pssm_splits	3
	***	hlms_shadowmap0_uv_min_x_int	0
	***	hlms_pose_normals	0
	***	hlms_pose_half	0
	***	hlms_shadowmap1_light_idx	0
	***	hlms_shadowmap0_uv_min_x_fract	0
	***	hlms_lights_spot	1
	***	shadowmap2_is_directional_light	1
	***	GL_ARB_shading_language_420pack	1
	***	uv_normal	0
	***	relaxed	1726237731
	***	hlms_alphablend	0
	***	hlms_num_shadow_map_textures	1
	***	hlms_shadowmap1_array_idx	0
	***	hlslvk	1841745752
	***	hlms_shadowmap1_uv_min_x_int	0
	***	uv_detail3	0
	***	hlms_shadow_uses_depth_texture	1
	***	ltcMatrix	1
	***	normal_map	0
	***	hlms_shadowmap1	0
	***	needs_env_brdf	1
	***	hlms_shadowmap2_uv_max_x_fract	0
	***	pcf	3
	***	uv_detail1	0
	***	fresnel_workflow	0
	***	hlms_shadowmap2_uv_min_y_fract	28571
	***	shadowmap1_is_directional_light	1
	***	full32	-2126167738
	***	perceptual_roughness	1
	***	alpha_test_shadow_caster_only	0
	***	materials_per_buffer	240
	***	hw_gamma_read	1
	***	hlms_skeleton	0
	***	hlms_shadowmap1_uv_max_y_int	0
	***	midf16	-1978079318
	***	hlms_shadowmap2_uv_min_x_int	0
	***	hlms_shadowmap1_uv_max_x_int	0
	***	syntax	-338983575
	***	hlms_lights_point	1
	***	metal	-1698855755
	***	hlms_fog	1
	***	GL_ARB_base_instance	1
	***	s_lights_directional_non_caster	1
	***	uv_detail0	0
	***	uv_diffuse	0
	***	needs_refl_dir	1
	***	hlms_pssm_blend	1
	***	uv_detail_nm0	0
	***	GL3+	450
	***	atmosky_npr	3
	***	hlms_shadowmap2_light_idx	0
	***	shadowmap0_is_directional_light	1
	***	hlms_shadowmap0_array_idx	0
	***	hlms_render_depth_only	0
	***	num_pass_const_buffers	4
	***	uv_detail2	0
	***	hlms_shadowmap1_uv_max_x_fract	50000
	***	hlms_shadowmap0_uvs_fulltex	1
	***	hlms_qtangent	1
	***	hlms_shadowmap1_uv_min_y_int	0
	***	uv_roughness	0
	***	receive_shadows	1
	***	hlms_pssm_fade	1
	***	clear_coat	0
	***	hlms_shadowmap0	0
	***	needs_view_dir	1
	***	hlms_shadowmap2_uvs_fulltex	1
	***	set1_texture_slot_end	3
	***	use_planar_reflections	0
	***	texShadowMap0	2
	***	hlms_shadowmap2_uv_min_y_int	0
	***	ambient_hemisphere	1
	***	ltc_texture_available	1
	***	glslvk	-338983575
	***	hlms_shadowmap0_uv_max_y_fract	28571
	***	hlsl	-334286542
	***	hlms_shadowmap0_uv_max_y_int	0
	***	normal_weight	0
	***	GL_ARB_texture_buffer_range	1
	DONE DUMPING PROPERTIES
	DONE DUMPING PIECES
#endif


	#version 450 core







	#extension GL_ARB_shading_language_420pack: require
	#define layout_constbuffer(x) layout( std140, x )





	#define bufferFetch texelFetch
	#define structuredBufferFetch texelFetch



	#define min3( a, b, c ) min( a, min( b, c ) )
	#define max3( a, b, c ) max( a, max( b, c ) )


#define float2 vec2
#define float3 vec3
#define float4 vec4

#define int2 ivec2
#define int3 ivec3
#define int4 ivec4

#define uint2 uvec2
#define uint3 uvec3
#define uint4 uvec4

#define float2x2 mat2
#define float3x3 mat3
#define float4x4 mat4
#define ogre_float4x3 mat3x4

#define ushort uint
#define ushort3 uint3
#define ushort4 uint4

//Short used for read operations. It's an int in GLSL & HLSL. An ushort in Metal
#define rshort int
#define rshort2 int2
#define rint int
//Short used for write operations. It's an int in GLSL. An ushort in HLSL & Metal
#define wshort2 int2
#define wshort3 int3

#define toFloat3x3( x ) mat3( x )
#define buildFloat3x3( row0, row1, row2 ) mat3( row0, row1, row2 )

// Let's explain this madness:
//
// We use the keyword "midf" because "half" is already taken on Metal.
//
// When precision_mode == full32 midf is float. Nothing weird
//
// When precision_mode == midf16, midf and midf_c map both to float16_t. It's similar to full32
// but literals need to be prefixed with _h()
//
// Thus, what happens if we resolve some of the macros, we end up with:
//		float16_t a = 1.0f;						// Error
//		float16_t b = _h( 1.0f );				// OK!
//		float16_t c = float16_t( someFloat );	// OK!
//
// But when precision_mode == relaxed; we have the following problem:
//		mediump float a = 1.0f;							// Error
//		mediump float b = _h( 1.0f );					// OK!
//		mediump float c = mediump float( someFloat );	// Invalid syntax!
//
// That's where 'midf_c' comes into play. The "_c" means cast or construct. Hence we do instead:
//		midf c = midf( someFloat );		// Will turn into invalid syntax on relaxed!
//		midf c = midf_c( someFloat );	// OK!
//
// Therefore datatypes are declared with midf. And casts and constructors are with midf_c
// Proper usage is as follows:
//		midf b = _h( 1.0f );
//		midf b = midf_c( someFloat );
//		midf c = midf3_c( 1.0f, 2.0f, 3.0f );
//
// Using this convention ensures that code will compile with all 3 precision modes.
// Breaking this convention means one or more of the modes (except full32) will not compile.

	#define _h(x) (x)

	#define midf float
	#define midf2 vec2
	#define midf3 vec3
	#define midf4 vec4
	#define midf2x2 mat2
	#define midf3x3 mat3
	#define midf4x4 mat4

	#define midf_c float
	#define midf2_c vec2
	#define midf3_c vec3
	#define midf4_c vec4
	#define midf2x2_c mat2
	#define midf3x3_c mat3
	#define midf4x4_c mat4

	#define toMidf3x3( x ) mat3( x )
	#define buildMidf3x3( row0, row1, row2 ) mat3( row0, row1, row2 )

	#define ensureValidRangeF16(x)

	#define saturate(x) clamp( (x), 0.0, 1.0 )




#define mul( x, y ) ((x) * (y))
#define lerp mix
#define rsqrt inversesqrt
#define INLINE
#define NO_INTERPOLATION_PREFIX flat
#define NO_INTERPOLATION_SUFFIX

#define PARAMS_ARG_DECL
#define PARAMS_ARG


	#define inVs_vertexId gl_VertexIndex

#define inVs_vertex vertex
#define inVs_normal normal
#define inVs_tangent tangent
#define inVs_binormal binormal
#define inVs_blendWeights blendWeights
#define inVs_blendIndices blendIndices
#define inVs_qtangent qtangent
#define inVs_colour colour


	#define inVs_drawId drawId


#define finalDrawId inVs_drawId


	#define inVs_uv0 uv0

#define outVs_Position gl_Position
#define outVs_viewportIndex gl_ViewportIndex
#define outVs_clipDistance0 gl_ClipDistance[0]

#define gl_SampleMaskIn0 gl_SampleMaskIn[0]
#define reversebits bitfieldReverse

#define outPs_colour0 outColour


	#define OGRE_SampleArray2D( tex, sampler, uv, arrayIdx ) texture( sampler2DArray( tex, sampler ), vec3( uv, arrayIdx ) )
	#define OGRE_SampleArray2DLevel( tex, sampler, uv, arrayIdx, lod ) textureLod( sampler2DArray( tex, sampler ), vec3( uv, arrayIdx ), lod )
	#define OGRE_SampleArrayCubeLevel( tex, sampler, uv, arrayIdx, lod ) textureLod( samplerCubeArray( tex, sampler ), vec4( uv, arrayIdx ), lod )
	#define OGRE_SampleArray2DGrad( tex, sampler, uv, arrayIdx, ddx, ddy ) textureGrad( sampler2DArray( tex, sampler ), vec3( uv, arrayIdx ), ddx, ddy )

	#define OGRE_Load2DF16( tex, iuv, lod ) midf4_c( texelFetch( tex, ivec2( iuv ), lod ) )
	#define OGRE_Load2DMSF16( tex, iuv, subsample ) midf4_c( texelFetch( tex, iuv, subsample ) )
	#define OGRE_SampleArray2DF16( tex, sampler, uv, arrayIdx ) midf4_c( texture( sampler2DArray( tex, sampler ), vec3( uv, arrayIdx ) ) )
	#define OGRE_SampleArray2DLevelF16( tex, sampler, uv, arrayIdx, lod ) midf4_c( textureLod( sampler2DArray( tex, sampler ), vec3( uv, arrayIdx ), lod ) )
	#define OGRE_SampleArrayCubeLevelF16( tex, sampler, uv, arrayIdx, lod ) midf4_c( textureLod( samplerCubeArray( tex, sampler ), vec4( uv, arrayIdx ), lod ) )
	#define OGRE_SampleArray2DGradF16( tex, sampler, uv, arrayIdx, ddx, ddy ) midf4_c( textureGrad( sampler2DArray( tex, sampler ), vec3( uv, arrayIdx ), ddx, ddy ) )

	float4 OGRE_Sample( texture2D t, sampler s, float2 uv ) { return texture( sampler2D( t, s ), uv ); }
	float4 OGRE_Sample( texture3D t, sampler s, float3 uv ) { return texture( sampler3D( t, s ), uv ); }
	float4 OGRE_Sample( textureCube t, sampler s, float3 uv ) { return texture( samplerCube( t, s ), uv ); }

	float4 OGRE_SampleLevel( texture2D t, sampler s, float2 uv, float lod ) { return textureLod( sampler2D( t, s ), uv, lod ); }
	float4 OGRE_SampleLevel( texture3D t, sampler s, float3 uv, float lod ) { return textureLod( sampler3D( t, s ), uv, lod ); }
	float4 OGRE_SampleLevel( textureCube t, sampler s, float3 uv, float lod ) { return textureLod( samplerCube( t, s ), uv, lod ); }

	float4 OGRE_SampleGrad( texture2D t, sampler s, float2 uv, float2 myDdx, float2 myDdy ) { return textureGrad( sampler2D( t, s ), uv, myDdx, myDdy ); }
	float4 OGRE_SampleGrad( texture3D t, sampler s, float3 uv, float3 myDdx, float3 myDdy ) { return textureGrad( sampler3D( t, s ), uv, myDdx, myDdy ); }
	float4 OGRE_SampleGrad( textureCube t, sampler s, float3 uv, float3 myDdx, float3 myDdy ) { return textureGrad( samplerCube( t, s ), uv, myDdx, myDdy ); }

	midf4 OGRE_SampleF16( texture2D t, sampler s, float2 uv ) { return midf4_c( texture( sampler2D( t, s ), uv ) ); }
	midf4 OGRE_SampleF16( texture3D t, sampler s, float3 uv ) { return midf4_c( texture( sampler3D( t, s ), uv ) ); }
	midf4 OGRE_SampleF16( textureCube t, sampler s, float3 uv ) { return midf4_c( texture( samplerCube( t, s ), uv ) ); }

	midf4 OGRE_SampleLevelF16( texture2D t, sampler s, float2 uv, float lod ) { return midf4_c( textureLod( sampler2D( t, s ), uv, lod ) ); }
	midf4 OGRE_SampleLevelF16( texture3D t, sampler s, float3 uv, float lod ) { return midf4_c( textureLod( sampler3D( t, s ), uv, lod ) ); }
	midf4 OGRE_SampleLevelF16( textureCube t, sampler s, float3 uv, float lod ) { return midf4_c( textureLod( samplerCube( t, s ), uv, lod ) ); }

	midf4 OGRE_SampleGradF16( texture2D t, sampler s, float2 uv, float2 myDdx, float2 myDdy ) { return midf4_c( textureGrad( sampler2D( t, s ), uv, myDdx, myDdy ) ); }
	midf4 OGRE_SampleGradF16( texture3D t, sampler s, float3 uv, float3 myDdx, float3 myDdy ) { return midf4_c( textureGrad( sampler3D( t, s ), uv, myDdx, myDdy ) ); }
	midf4 OGRE_SampleGradF16( textureCube t, sampler s, float3 uv, float3 myDdx, float3 myDdy ) { return midf4_c( textureGrad( samplerCube( t, s ), uv, myDdx, myDdy ) ); }

#define OGRE_ddx( val ) dFdx( val )
#define OGRE_ddy( val ) dFdy( val )
#define OGRE_Load2D( tex, iuv, lod ) texelFetch( tex, ivec2( iuv ), lod )
#define OGRE_LoadArray2D( tex, iuv, arrayIdx, lod ) texelFetch( tex, ivec3( iuv, arrayIdx ), lod )
#define OGRE_Load2DMS( tex, iuv, subsample ) texelFetch( tex, iuv, subsample )

#define OGRE_Load3D( tex, iuv, lod ) texelFetch( tex, ivec3( iuv ), lod )

#define bufferFetch1( buffer, idx ) texelFetch( buffer, idx ).x


	#define OGRE_SAMPLER_ARG_DECL( samplerName ) , sampler samplerName
	#define OGRE_SAMPLER_ARG( samplerName ) , samplerName

	#define CONST_BUFFER( bufferName, bindingPoint ) layout_constbuffer(ogre_B##bindingPoint) uniform bufferName
	#define CONST_BUFFER_STRUCT_BEGIN( structName, bindingPoint ) layout_constbuffer(ogre_B##bindingPoint) uniform structName
	#define CONST_BUFFER_STRUCT_END( variableName ) variableName

	#define ReadOnlyBufferF( slot, varType, varName ) layout(std430, ogre_R##slot) readonly restrict buffer _##varName { varType varName[]; }
	#define ReadOnlyBufferU ReadOnlyBufferF
	#define readOnlyFetch( bufferVar, idx ) bufferVar[idx]
	#define readOnlyFetch1( bufferVar, idx ) bufferVar[idx]



#define OGRE_Texture3D_float4 texture3D

#define OGRE_ArrayTex( declType, varName, arrayCount ) declType varName[arrayCount]

#define FLAT_INTERPOLANT( decl, bindingPoint ) flat decl
#define INTERPOLANT( decl, bindingPoint ) decl

#define OGRE_OUT_REF( declType, variableName ) out declType variableName
#define OGRE_INOUT_REF( declType, variableName ) inout declType variableName

#define OGRE_ARRAY_START( type ) type[](
#define OGRE_ARRAY_END )



out gl_PerVertex
{
	vec4 gl_Position;

};

layout(std140) uniform;


	
		#define worldViewMat worldView
	

	
#define UNPACK_MAT4( matrixBuf, pixelIdx ) mat4( matrixBuf[(pixelIdx) << 2u], matrixBuf[((pixelIdx) << 2u)+1u], matrixBuf[((pixelIdx) << 2u)+2u], matrixBuf[((pixelIdx) << 2u)+3u] )

	
#define UNPACK_MAT4x3( matrixBuf, pixelIdx ) mat3x4( matrixBuf[(pixelIdx) << 2u], matrixBuf[((pixelIdx) << 2u)+1u], matrixBuf[((pixelIdx) << 2u)+2u] )


	// START UNIFORM DECLARATION
	
struct ShadowReceiverData
{
	float4x4 texViewProj;

	float2 shadowDepthRange;
	float normalOffsetBias;
	float padding;
	float4 invShadowMapSize;
};

struct Light
{
	
		float4 position;	//.w contains the objLightMask
	
	float4 diffuse;		//.w contains numNonCasterDirectionalLights
	float3 specular;

	float3 attenuation;
	//Spotlights:
	//  spotDirection.xyz is direction
	//  spotParams.xyz contains falloff params
	float4 spotDirection;
	float4 spotParams;


#define lightTexProfileIdx spotDirection.w
};

#define numNonCasterDirectionalLights lights[0].diffuse.w

#define areaLightDiffuseMipmapStart areaApproxLights[0].diffuse.w
#define areaLightNumMipmapsSpecFactor areaApproxLights[0].specular.w

#define numAreaApproxLights areaApproxLights[0].doubleSided.y
#define numAreaApproxLightsWithMask areaApproxLights[0].doubleSided.z

#define numAreaLtcLights areaLtcLights[0].points[0].w
#define numAreaLtcLights areaLtcLights[0].points[0].w

struct AreaLight
{
	
		float4 position;	//.w contains the objLightMask
	
	float4 diffuse;		//[0].w contains diffuse mipmap start
	float4 specular;	//[0].w contains mipmap scale
	float4 attenuation;	//.w contains texture array idx
	//Custom 2D Shape:
	//  direction.xyz direction
	//  direction.w invHalfRectSize.x
	//  tangent.xyz tangent
	//  tangent.w invHalfRectSize.y
	float4 direction;
	float4 tangent;
	float4 doubleSided;	//.y contains numAreaApproxLights
						//.z contains numAreaApproxLightsWithMask
	
};

struct AreaLtcLight
{
	
		float4 position;	//.w contains the objLightMask
	
	float4 diffuse;			//.w contains attenuation range
	float4 specular;		//.w contains doubleSided
	float4 points[4];		//.w contains numAreaLtcLights
							//points[1].w, points[2].w, points[3].w contain obbFadeFactorLtc.xyz
	
};





//Uniforms that change per pass
CONST_BUFFER_STRUCT_BEGIN( PassBuffer, 0 )
{
	//Vertex shader (common to both receiver and casters)

	float4x4 viewProj;







	//Vertex shader
	float4x4 view;
	ShadowReceiverData shadowRcv[3];

	

	//-------------------------------------------------------------------------

	//Pixel shader
	float3x3 invViewMatCubemap;


	float4 pccVctMinDistance_invPccVctInvDistance_rightEyePixelStartX_envMapNumMipmaps;

	float4 aspectRatio_planarReflNumMips_unused2;

	float2 invWindowRes;
	float2 windowResolution;


	float4 ambientUpperHemi;


	float4 ambientLowerHemi;
	float4 ambientHemisphereDir;







	float pssmSplitPoints0;
	float pssmSplitPoints1;
	float pssmSplitPoints2;

	float pssmBlendPoints0;
	float pssmBlendPoints1;

	float pssmFadePoint;



	Light lights[1];
	
	
// !use_light_buffers





	



	
	

	

#define pccVctMinDistance		pccVctMinDistance_invPccVctInvDistance_rightEyePixelStartX_envMapNumMipmaps.x
#define invPccVctInvDistance	pccVctMinDistance_invPccVctInvDistance_rightEyePixelStartX_envMapNumMipmaps.y
#define rightEyePixelStartX		pccVctMinDistance_invPccVctInvDistance_rightEyePixelStartX_envMapNumMipmaps.z
#define envMapNumMipmaps		pccVctMinDistance_invPccVctInvDistance_rightEyePixelStartX_envMapNumMipmaps.w

#define aspectRatio			aspectRatio_planarReflNumMips_unused2.x
#define planarReflNumMips	aspectRatio_planarReflNumMips_unused2.y
}
CONST_BUFFER_STRUCT_END( passBuf );



#define light0Buf		passBuf
#define light1Buf		passBuf
#define light2Buf		passBuf

// use_light_buffers


	
	
	struct AtmoSettings
	{
		float densityCoeff;
		float lightDensity;
		float sunHeight;
		float sunHeightWeight;

		float4 skyLightAbsorption;
		float4 sunAbsorption;
		float4 cameraDisplacement;
		float4 packedParams1;
		float4 packedParams2;
		float4 packedParams3;

		float fogDensity;
		float fogBreakMinBrightness;
		float fogBreakFalloff;
		float padding0;
	};

	
		CONST_BUFFER( AtmoSettingsBuf, 3 )
		{
			AtmoSettings atmoSettings;
		};
	

	
	// END UNIFORM DECLARATION

	
		
	
		vec3 xAxis( vec4 qQuat )
		{
			float fTy  = 2.0 * qQuat.y;
			float fTz  = 2.0 * qQuat.z;
			float fTwy = fTy * qQuat.w;
			float fTwz = fTz * qQuat.w;
			float fTxy = fTy * qQuat.x;
			float fTxz = fTz * qQuat.x;
			float fTyy = fTy * qQuat.y;
			float fTzz = fTz * qQuat.z;

			return vec3( 1.0-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy );
		}
	
	

		
	

    
			
				
					#define shadowMap0LightDir light0Buf.lights[0].position.xyz
				
				
				
			
				
					#define shadowMap1LightDir light0Buf.lights[0].position.xyz
				
				
				
			
				
					#define shadowMap2LightDir light0Buf.lights[0].position.xyz
				
				
				
			
			
				#define hlms_shadowmap0_uv_min float2( 0.0, 0.0 )
				#define hlms_shadowmap0_uv_max float2( 1.0, 0.28571 )
				
					
						#define hlms_shadowmap0_uv_param , hlms_shadowmap0_uv_min, hlms_shadowmap0_uv_max
					
				
			
				#define hlms_shadowmap1_uv_min float2( 0.0, 0.28571 )
				#define hlms_shadowmap1_uv_max float2( 0.50000, 0.42857 )
				
					
						#define hlms_shadowmap1_uv_param , hlms_shadowmap1_uv_min, hlms_shadowmap1_uv_max
					
				
			
				#define hlms_shadowmap2_uv_min float2( 0.50000, 0.28571 )
				#define hlms_shadowmap2_uv_max float2( 1.0, 0.42857 )
				
					
						#define hlms_shadowmap2_uv_param , hlms_shadowmap2_uv_min, hlms_shadowmap2_uv_max
					
				
			

			
		
			// Perform normal offset bias. See https://github.com/OGRECave/ogre-next/issues/100
			INLINE float3 getNormalOffsetBias( midf3 worldNormal, midf3 viewSpaceNormal,
											   float3 lightDir, float shadowMapTexSize,
											   float depthRange, float normalOffsetBias
			
											   )
			
			{
				float tmpNdotL = saturate( dot( lightDir.xyz, float3( viewSpaceNormal.xyz ) ) );

				

				return ( ( 1.0f - tmpNdotL ) * normalOffsetBias * float3( worldNormal.xyz ) * shadowMapTexSize );
			}
		
			// Perform normal offset bias. See https://github.com/OGRECave/ogre-next/issues/100
			INLINE float3 getNormalOffsetBias( midf3 worldNormal, midf3 viewSpaceNormal,
											   float3 lightDir, float shadowMapTexSize,
											   float depthRange, float normalOffsetBias
			
											   , float2 minUV, float2 maxUV )
			
			{
				float tmpNdotL = saturate( dot( lightDir.xyz, float3( viewSpaceNormal.xyz ) ) );

				
					shadowMapTexSize /= maxUV.x - minUV.x;
				

				return ( ( 1.0f - tmpNdotL ) * normalOffsetBias * float3( worldNormal.xyz ) * shadowMapTexSize );
			}
		
	
		
	

// See https://en.wikipedia.org/wiki/Rayleigh_distribution
// It's inspired, not fully based.
//
// The formula also gives us the nice property that for inputs
// where absorption is in range [0; 1] the output i also in range [0; 1]
midf3 getSkyRayleighAbsorption( midf3 vDir, const midf density )
{
	midf3 absorption = -density * vDir;
	absorption = exp2( absorption ) * _h( 2.0 );
	return absorption;
}

midf3 pow3( midf3 v, midf e )
{
	return midf3_c( pow( v.x, e ), pow( v.y, e ), pow( v.z, e ) );
}

// 



vulkan_layout( OGRE_POSITION ) in vec4 vertex;


vulkan_layout( OGRE_NORMAL ) in midf4 qtangent;






	vulkan_layout( OGRE_TEXCOORD0 ) in vec2 uv0;


	vulkan_layout( OGRE_DRAWID ) in uint drawId;





	vulkan_layout( location = 0 ) out block
	{
		
	
		
			FLAT_INTERPOLANT( ushort drawId, 0 );
		
	

	
		
			INTERPOLANT( float3 pos, 1 );
			INTERPOLANT( midf3 normal, 2 );
			
		
		
			INTERPOLANT( float2 uv0, 3 );

		
			
				
					INTERPOLANT( float4 posL0, 4 );
				
			
				
					INTERPOLANT( float4 posL1, 5 );
				
			
				
					INTERPOLANT( float4 posL2, 6 );
				
			
		

		INTERPOLANT( float depth, 7 );
		

		

		
			// fog.xyz = colour
			INTERPOLANT( midf3 fog, 8 );
		
	
	

	} outVs;


// START UNIFORM GL DECLARATION
ReadOnlyBufferF( 0, float4, worldMatBuf );



// END UNIFORM GL DECLARATION

void main()
{

    
	
	// Define inputPos using inVs_vertex.
	
		#define inputPos inVs_vertex
	

	// Define inputNormal and inputTangent using inVs_normal, inVs_tangent, inVs_qtangent
	
		//Decode qTangent to TBN with reflection
		const midf4 qTangent = normalize( inVs_qtangent );
		midf3 inputNormal = xAxis( qTangent );
		
	

	
		ogre_float4x3 worldMat = UNPACK_MAT4x3( worldMatBuf, inVs_drawId << 1u);
		
			float4x4 worldView = UNPACK_MAT4( worldMatBuf, (inVs_drawId << 1u) + 1u );
		

		float4 worldPos = float4( mul(inVs_vertex, worldMat).xyz, 1.0f );
		
			// We need worldNorm for normal offset bias
			midf3 worldNorm = mul( inputNormal, toMidf3x3( worldMat ) ).xyz;
		
	

	

	

	
	
	
	//Lighting is in view space
		outVs.pos		= mul( inputPos, worldViewMat ).xyz;
		outVs.normal	= mul( inputNormal, toMidf3x3( worldViewMat ) );
	
	
        
			
				outVs_Position = mul( worldPos, passBuf.viewProj );
			
		
	


	
				float3 normalOffsetBias = float3( 0, 0, 0 );
				
					
						
							normalOffsetBias = getNormalOffsetBias( worldNorm, outVs.normal, shadowMap0LightDir,
																	passBuf.shadowRcv[0].invShadowMapSize.x,
																	passBuf.shadowRcv[0].shadowDepthRange.y,
																	passBuf.shadowRcv[0].normalOffsetBias
																	hlms_shadowmap0_uv_param );
						
						outVs.posL0 = mul( float4(worldPos.xyz + normalOffsetBias, 1.0f), passBuf.shadowRcv[0].texViewProj );

						

						
					
				
					
						
							normalOffsetBias = getNormalOffsetBias( worldNorm, outVs.normal, shadowMap1LightDir,
																	passBuf.shadowRcv[1].invShadowMapSize.x,
																	passBuf.shadowRcv[1].shadowDepthRange.y,
																	passBuf.shadowRcv[1].normalOffsetBias
																	hlms_shadowmap1_uv_param );
						
						outVs.posL1 = mul( float4(worldPos.xyz + normalOffsetBias, 1.0f), passBuf.shadowRcv[1].texViewProj );

						

						
					
				
					
						
							normalOffsetBias = getNormalOffsetBias( worldNorm, outVs.normal, shadowMap2LightDir,
																	passBuf.shadowRcv[2].invShadowMapSize.x,
																	passBuf.shadowRcv[2].shadowDepthRange.y,
																	passBuf.shadowRcv[2].normalOffsetBias
																	hlms_shadowmap2_uv_param );
						
						outVs.posL2 = mul( float4(worldPos.xyz + normalOffsetBias, 1.0f), passBuf.shadowRcv[2].texViewProj );

						

						
					
				

				outVs.depth = outVs_Position.w;
			
	

	
// clang-format off
#define p_densityCoeff			midf_c( atmoSettings.densityCoeff )
#define p_lightDensity			midf_c( atmoSettings.lightDensity )
#define p_sunHeight				midf_c( atmoSettings.sunHeight )
#define p_sunHeightWeight		midf_c( atmoSettings.sunHeightWeight )
#define p_skyLightAbsorption	midf3_c( atmoSettings.skyLightAbsorption.xyz )
#define p_sunAbsorption			midf3_c( atmoSettings.sunAbsorption.xyz )
#define p_cameraDisplacement	midf3_c( atmoSettings.cameraDisplacement.xyz )
#define p_mieAbsorption			midf3_c( atmoSettings.packedParams1.xyz )
#define p_finalMultiplier		midf_c( atmoSettings.packedParams1.w )
#define p_sunDir				midf3_c( atmoSettings.packedParams2.xyz )
#define p_borderLimit			midf_c( atmoSettings.packedParams2.w )
#define p_skyColour				midf3_c( atmoSettings.packedParams3.xyz )
#define p_densityDiffusion		midf_c( atmoSettings.packedParams3.w )
// clang-format on

const float3 cameraPos = float3( atmoSettings.skyLightAbsorption.w, atmoSettings.sunAbsorption.w,
								 atmoSettings.cameraDisplacement.w );
float3 cameraDir = worldPos.xyz - cameraPos;
float distToCamera = length( cameraDir );
midf3 atmoCameraDir = midf3_c( cameraDir * ( 1.0f / distToCamera ) );

const midf LdotV = max( dot( atmoCameraDir, p_sunDir ), _h( 0.0 ) );

atmoCameraDir.y +=
	p_densityDiffusion * _h( 0.075 ) * ( _h( 1.0 ) - atmoCameraDir.y ) * ( _h( 1.0 ) - atmoCameraDir.y );
atmoCameraDir += p_cameraDisplacement;
atmoCameraDir = normalize( atmoCameraDir );

atmoCameraDir.y = max( atmoCameraDir.y, p_borderLimit );
atmoCameraDir.y = atmoCameraDir.y * _h( 0.9 ) + _h( 0.1 );
atmoCameraDir = normalize( atmoCameraDir );

const midf LdotV360 = dot( atmoCameraDir, p_sunDir ) * _h( 0.5 ) + _h( 0.5 );

// ptDensity gets smaller as sunHeight gets bigger
// ptDensity gets smaller as atmoCameraDir.y gets bigger
const midf ptDensity =
	p_densityCoeff /
	pow( max( atmoCameraDir.y / ( _h( 1.0 ) - p_sunHeight ), _h( 0.0035 ) ), p_densityDiffusion );

const midf antiMie = max( p_sunHeightWeight, _h( 0.08 ) );

const midf3 skyAbsorption = getSkyRayleighAbsorption( p_skyColour, ptDensity );
const midf3 skyColourGradient = pow3( exp2( -atmoCameraDir.y / p_skyColour ), _h( 1.5 ) );

const midf mie = LdotV360;

midf3 atmoColour = midf3_c( 0.0f, 0.0f, 0.0f );

const midf3 sharedTerms = skyColourGradient * skyAbsorption;

atmoColour += antiMie * sharedTerms * p_sunAbsorption;
atmoColour += ( mie * ptDensity * p_lightDensity ) * sharedTerms * p_skyLightAbsorption;
atmoColour += mie * p_mieAbsorption;
atmoColour *= p_lightDensity;

atmoColour *= p_finalMultiplier;

outVs.fog.xyz = atmoColour;
// 

	/// hlms_uv_count will be 0 on shadow caster passes w/out alpha test
	
		outVs.uv0 = inVs_uv0;


	
		outVs.drawId = inVs_drawId;
	


	

	

	

	
}
