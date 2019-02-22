#include "MaterialParser.h"
#include "..\Spore\ArgScript\IBlock.h"
#include "..\Spore\ArgScript\ICommand.h"
#include "..\Spore\ArgScript\Line.h"
#include "..\Spore\Hash.h"
#include "..\ModAPI\MainUtilities.h"
#include "..\Spore\Graphics\ITextureManager.h"

#include <ModAPI\ShaderConstantsManager.h>

#include <EASTL\string.h>

using namespace ModAPI;

typedef MaterialConfig::ShaderConstant::DataValue<void*> DefaultValue;
typedef MaterialConfig::ShaderConstant::DataValue<int> IntValue;
typedef MaterialConfig::ShaderConstant::DataValue<int> NameValue;
typedef MaterialConfig::ShaderConstant::DataValue<float> FloatValue;
typedef MaterialConfig::ShaderConstant::DataValue<char> CharValue;
typedef MaterialConfig::ShaderConstant::DataValue<short> ShortValue;
typedef MaterialConfig::ShaderConstant::DataValue<bool> BoolValue;

MaterialParser::MaterialParser(ArgScript::FormatParser* formatParser)
	:
	mFormatParser(formatParser), mMaterials()
{
	ConfigureFormatParser();
}

MaterialParser::~MaterialParser() 
{
}

void MaterialParser::ConfigureFormatParser()
{

	class AS_material : public ArgScript::IBlock
	{
	public:
		intrusive_ptr<MaterialConfig> materialConfig;
		MaterialParser* dst;
		//eastl::string nameCopy;
		char* nameCopy;

		AS_material(MaterialParser* dst_)
			: dst(dst_), materialConfig(nullptr), nameCopy(nullptr)
		{
		}
		~AS_material()
		{
			if (nameCopy != nullptr) { 
				delete nameCopy;
			}
		}

		virtual void ParseLine(const ArgScript::Line& line)
		{
			ArgScript::Arguments args = line.GetArguments(1);
			const char* name = args[0];
			/*unsigned long ID;

			if (name[0] == '0' && name[1] == 'x')
			{
				ID = this->mpFormatParser->ParseInt(name);
			}
			else
			{
				ID = Hash::FNV(name);
			}*/

			this->materialConfig = new MaterialConfig();
			// this->materialConfig->ID = ID;
			this->materialConfig->name = name;

			size_t size = strlen(name);

			// MessageBoxA(NULL, ("STR LEN: " + eastl::to_string(size)).c_str(), "BREAKPOINT", MB_OK);



			/*nameCopy = new char[size];
			strcpy_s(nameCopy, size, name);*/

			//nameCopy = eastl::string(name);

			nameCopy = new char[size + 1];
			nameCopy[size] = 0;

			memcpy(nameCopy, name, size);

			this->dst->mMaterials[nameCopy] = this->materialConfig;

			this->mpFormatParser->AddBlock(this);

		}
		virtual void SetData(ArgScript::FormatParser* formatParser, void* data)
		{
			IBlock::SetData(formatParser, &materialConfig);

			class AS_materialID : public ArgScript::ICommand
			{
			public:
				virtual void ParseLine(const ArgScript::Line& line)
				{
					ArgScript::Arguments args = line.GetArguments(1);
					if (args[0][0] == '0' && args[0][1] == 'x')
					{
						(*(MaterialConfig**) this->mpData)->materialID = this->mpFormatParser->ParseInt(args[0]);
					}
					else
					{
						(*(MaterialConfig**) this->mpData)->materialID = Hash::FNV(args[0]);
					}
				}
			};
			this->AddParser("materialID", new AS_materialID());

			class AS_primitiveType : public ArgScript::ICommand
			{
			public:
				virtual void ParseLine(const ArgScript::Line& line)
				{
					ArgScript::Arguments args = line.GetArguments(1);
					(*(MaterialConfig**) this->mpData)->primitiveType = ArgScript::Line::GetEnum(args[0], MaterialParser::states);
				}
			};
			this->AddParser("primitiveType", new AS_primitiveType());

			class AS_materialColor : public ArgScript::ICommand
			{
			public:
				virtual void ParseLine(const ArgScript::Line& line)
				{
					size_t argCount;
					ArgScript::Arguments args = line.GetArgumentsRange(&argCount, 0, 1);

					if (argCount > 0)
					{
						(*(MaterialConfig**) this->mpData)->materialColor = this->mpFormatParser->ParseColorRGBA(args[0]);
						(*(MaterialConfig**) this->mpData)->useMaterialColor = true;

						ArgScript::Arguments optionArgs = line.GetOption("alpha", 1);
						if (optionArgs != nullptr)
						{
							(*(MaterialConfig**) this->mpData)->materialColor.a = this->mpFormatParser->ParseFloat(optionArgs[0]);
						}
					}
					else
					{
						(*(MaterialConfig**) this->mpData)->useMaterialColor = false;
					}
				}
			};
			this->AddParser("materialColor", new AS_materialColor());

			class AS_ambientColor : public ArgScript::ICommand
			{
			public:
				virtual void ParseLine(const ArgScript::Line& line)
				{
					size_t argCount;
					ArgScript::Arguments args = line.GetArgumentsRange(&argCount, 0, 1);

					if (argCount > 0)
					{
						(*(MaterialConfig**) this->mpData)->ambientColor = this->mpFormatParser->ParseColorRGB(args[0]);
						(*(MaterialConfig**) this->mpData)->useAmbientColor = true;
					}
					else
					{
						(*(MaterialConfig**) this->mpData)->useAmbientColor = false;
					}
				}
			};
			this->AddParser("ambientColor", new AS_ambientColor());

			class AS_renderState : public ArgScript::ICommand
			{
			public:
				virtual void ParseLine(const ArgScript::Line& line)
				{
					ArgScript::Arguments args = line.GetArguments(2);

					(*(MaterialConfig**) this->mpData)->renderStates.push_back(pair<int, int>(
						ParseState(this->mpFormatParser, args[0]), ParseState(this->mpFormatParser, args[1])));
				}
			};
			this->AddParser("renderState", new AS_renderState());

			class AS_shaderConst : public ArgScript::IBlock
			{
			public:
				MaterialConfig::ShaderConstant* shConst;

				virtual void ParseLine(const ArgScript::Line& line)
				{
					shConst = new MaterialConfig::ShaderConstant();
					ArgScript::Arguments args = line.GetArguments(1);

					shConst->index = ModAPI::ModAPIUtils::GetShaderConstantsManager()->GetIndex(args[0]);

					(*(MaterialConfig**) this->mpData)->shaderConstants.push_back(shConst);

					this->mpFormatParser->SetCurrentParser(this);
				}
				virtual void SetData(ArgScript::FormatParser* formatParser, void* data)
				{
					DefaultSetData(formatParser, &shConst);

					class AS_int : public ArgScript::ICommand
					{
						virtual void ParseLine(const ArgScript::Line& line)
						{

							size_t argCount;
							ArgScript::Arguments args = line.GetArgumentsRange(&argCount, 1, 2);
							(*(MaterialConfig::ShaderConstant**) this->mpData)->data.push_back(
								(DefaultValue*) new IntValue(this->mpFormatParser->ParseInt(args[argCount - 1])));
						}
					};
					this->AddParser("int", new AS_int());

					class AS_float : public ArgScript::ICommand
					{
						virtual void ParseLine(const ArgScript::Line& line)
						{
							size_t argCount;
							ArgScript::Arguments args = line.GetArgumentsRange(&argCount, 1, 2);
							(*(MaterialConfig::ShaderConstant**) this->mpData)->data.push_back(
								(DefaultValue*) new FloatValue(this->mpFormatParser->ParseFloat(args[argCount - 1])));
						}
					};
					this->AddParser("float", new AS_float());

					class AS_char : public ArgScript::ICommand
					{
						virtual void ParseLine(const ArgScript::Line& line)
						{
							size_t argCount;
							ArgScript::Arguments args = line.GetArgumentsRange(&argCount, 1, 2);
							(*(MaterialConfig::ShaderConstant**) this->mpData)->data.push_back(
								(DefaultValue*) new CharValue(this->mpFormatParser->ParseInt(args[argCount - 1])));
						}
					};
					this->AddParser("char", new AS_char());

					class AS_short : public ArgScript::ICommand
					{
						virtual void ParseLine(const ArgScript::Line& line)
						{
							size_t argCount;
							ArgScript::Arguments args = line.GetArgumentsRange(&argCount, 1, 2);
							(*(MaterialConfig::ShaderConstant**) this->mpData)->data.push_back(
								(DefaultValue*) new ShortValue((short) this->mpFormatParser->ParseInt(args[argCount - 1])));
						}
					};
					this->AddParser("short", new AS_short());

					class AS_bool : public ArgScript::ICommand
					{
						virtual void ParseLine(const ArgScript::Line& line)
						{
							size_t argCount;
							ArgScript::Arguments args = line.GetArgumentsRange(&argCount, 1, 2);
							(*(MaterialConfig::ShaderConstant**) this->mpData)->data.push_back(
								(DefaultValue*) new BoolValue(this->mpFormatParser->ParseBool(args[argCount - 1])));
						}
					};
					this->AddParser("bool", new AS_bool());

					class AS_name : public ArgScript::ICommand
					{
						virtual void ParseLine(const ArgScript::Line& line)
						{
							size_t argCount;
							ArgScript::Arguments args = line.GetArgumentsRange(&argCount, 1, 2);
							(*(MaterialConfig::ShaderConstant**) this->mpData)->data.push_back(
								(DefaultValue*) new NameValue(Hash::FNV(args[argCount - 1])));
						}
					};
					this->AddParser("name", new AS_name());

					// once we have registered all parsers, we want to have the material as the data again
					DefaultSetData(formatParser, data);
				}
			};
			this->AddParser("shaderConst", new AS_shaderConst());

			class AS_textureSlot : public ArgScript::Block
			{
			public:
				MaterialConfig::TextureSlot* slot;

				virtual void ParseLine(const ArgScript::Line& line)
				{
					slot = new MaterialConfig::TextureSlot();
					ArgScript::Arguments args = line.GetArguments(1);

					slot->samplerIndex = this->mpFormatParser->ParseInt(args[0]);

					// parse the options
					args = line.GetOption("samplerStates", 1);
					if (args != nullptr)
					{
						slot->samplerStatesUnknown = this->mpFormatParser->ParseInt(args[0]);
					}
					else
					{
						slot->samplerStatesUnknown = 0;
					}

					args = line.GetOption("stageStates", 1);
					if (args != nullptr)
					{
						slot->stageStatesUnknown = this->mpFormatParser->ParseInt(args[0]);
					}
					else
					{
						slot->stageStatesUnknown = 0;
					}

					// push the slot

					(*(MaterialConfig**) this->mpData)->textureSlots.push_back(slot);

					this->mpFormatParser->SetCurrentParser(this);
				}
				virtual void SetData(ArgScript::FormatParser* formatParser, void* data)
				{
					DefaultSetData(formatParser, &slot);

					class AS_samplerState : public ArgScript::ICommand
					{
						virtual void ParseLine(const ArgScript::Line& line)
						{
							ArgScript::Arguments args = line.GetArguments(2);

							(*(MaterialConfig::TextureSlot**) this->mpData)->samplerStates.push_back(pair<int, int>(
								ParseState(this->mpFormatParser, args[0]), ParseState(this->mpFormatParser, args[1])));
						}
					};
					this->AddParser("samplerState", new AS_samplerState());

					class AS_stageState : public ArgScript::ICommand
					{
						virtual void ParseLine(const ArgScript::Line& line)
						{
							ArgScript::Arguments args = line.GetArguments(2);

							(*(MaterialConfig::TextureSlot**) this->mpData)->stageStates.push_back(pair<int, int>(
								ParseState(this->mpFormatParser, args[0]), ParseState(this->mpFormatParser, args[1])));
						}
					};
					this->AddParser("stageState", new AS_stageState());

					// once we have registered all parsers, we want to have the material as the data again
					DefaultSetData(formatParser, data);
				}
			};
			this->AddParser("textureSlot", new AS_textureSlot());
		}
	};
	mFormatParser->AddParser("material", new AS_material(this));


	class AS_exportMaterial : public ArgScript::ICommand
	{
	public:
		Graphics::Material material;
		MaterialParser* dst;
		AS_exportMaterial(MaterialParser* dst_)
			: dst(dst_)
		{
		}

		virtual void ParseLine(const ArgScript::Line& line)
		{
			this->material = Graphics::Material();

			ArgScript::Arguments args = line.GetArguments(1);

			this->mpFormatParser->ParseID(args[0], this->material.materialID);

			size_t argCount;
			args = line.GetOptionRange("materials", &argCount, 1, 4);

			if (args != nullptr)
			{
				this->material.nCompiledStates = static_cast<char>(argCount);
				for (unsigned int i = 0; i < argCount; i++) {

					auto it = this->dst->mMaterials.find(args[i]);
					if (it == this->dst->mMaterials.end()) {
						throw std::exception("Specified material does not exist.");
					}

					this->material.compiledStates[i] = it->second->CreateCompiledState();
				}
			}
			else
			{
				this->material.nCompiledStates = 0;
			}

			args = line.GetOptionRange("textures", &argCount, 1, 255);
			if (args != nullptr)
			{
				Graphics::TextureManager* texManager = Graphics::TextureManager::GetTextureManager();
				this->material.textures.reserve(argCount);

				for (unsigned int i = 0; i < argCount; i++) {

					int*** object = CALL_(GetAddress(0x67DE80, 0x67DD20, 0x67DD20), int***);

					unsigned long instanceID;
					unsigned long groupID;

					this->mpFormatParser->ParseID(args[i], instanceID, groupID);

					this->material.textures.push_back(texManager->GetRasterTexture(instanceID, groupID, 0));
				}
			}

			MaterialConfig::AddSporeMaterial(&this->material);
		}
	};
	mFormatParser->AddParser("exportMaterial", new AS_exportMaterial(this));
}

int MaterialParser::ParseState(ArgScript::FormatParser* formatParser, const char* state)
{
	if (state[0] == '0' && state[1] == 'x')
	{
		// hexadecimal number
		return formatParser->ParseInt(state);
	}
	else
	{
		int len = strlen(state);
		for (int i = 0; i < len; i++)
		{
			if (!isdigit(state[i]))
			{
				// it's not a number
				return ArgScript::Line::GetEnum(state, MaterialParser::states);
			}
		}

		// all characters were digits
		return formatParser->ParseInt(state);
	}
}

ArgScript::EnumValue MaterialParser::states[] = {
	{ "FALSE", 0 },
	{ "TRUE", 1 },
	{ "D3DRS_ZENABLE", 7 },
	{ "D3DRS_FILLMODE", 8 },
	{ "D3DRS_SHADEMODE", 9 },
	{ "D3DRS_ZWRITEENABLE", 14 },
	{ "D3DRS_ALPHATESTENABLE", 15 },
	{ "D3DRS_LASTPIXEL", 16 },
	{ "D3DRS_SRCBLEND", 19 },
	{ "D3DRS_DESTBLEND", 20 },
	{ "D3DRS_CULLMODE", 22 },
	{ "D3DRS_ZFUNC", 23 },
	{ "D3DRS_ALPHAREF", 24 },
	{ "D3DRS_ALPHAFUNC", 25 },
	{ "D3DRS_DITHERENABLE", 26 },
	{ "D3DRS_ALPHABLENDENABLE", 27 },
	{ "D3DRS_FOGENABLE", 28 },
	{ "D3DRS_SPECULARENABLE", 29 },
	{ "D3DRS_FOGCOLOR", 34 },
	{ "D3DRS_FOGTABLEMODE", 35 },
	{ "D3DRS_FOGSTART", 36 },
	{ "D3DRS_FOGEND", 37 },
	{ "D3DRS_FOGDENSITY", 38 },
	{ "D3DRS_RANGEFOGENABLE", 48 },
	{ "D3DRS_STENCILENABLE", 52 },
	{ "D3DRS_STENCILFAIL", 53 },
	{ "D3DRS_STENCILZFAIL", 54 },
	{ "D3DRS_STENCILPASS", 55 },
	{ "D3DRS_STENCILFUNC", 56 },
	{ "D3DRS_STENCILREF", 57 },
	{ "D3DRS_STENCILMASK", 58 },
	{ "D3DRS_STENCILWRITEMASK", 59 },
	{ "D3DRS_TEXTUREFACTOR", 60 },
	{ "D3DRS_WRAP0", 128 },
	{ "D3DRS_WRAP1", 129 },
	{ "D3DRS_WRAP2", 130 },
	{ "D3DRS_WRAP3", 131 },
	{ "D3DRS_WRAP4", 132 },
	{ "D3DRS_WRAP5", 133 },
	{ "D3DRS_WRAP6", 134 },
	{ "D3DRS_WRAP7", 135 },
	{ "D3DRS_CLIPPING", 136 },
	{ "D3DRS_LIGHTING", 137 },
	{ "D3DRS_AMBIENT", 139 },
	{ "D3DRS_FOGVERTEXMODE", 140 },
	{ "D3DRS_COLORVERTEX", 141 },
	{ "D3DRS_LOCALVIEWER", 142 },
	{ "D3DRS_NORMALIZENORMALS", 143 },
	{ "D3DRS_DIFFUSEMATERIALSOURCE", 145 },
	{ "D3DRS_SPECULARMATERIALSOURCE", 146 },
	{ "D3DRS_AMBIENTMATERIALSOURCE", 147 },
	{ "D3DRS_EMISSIVEMATERIALSOURCE", 148 },
	{ "D3DRS_VERTEXBLEND", 151 },
	{ "D3DRS_CLIPPLANEENABLE", 152 },
	{ "D3DRS_POINTSIZE", 154 },
	{ "D3DRS_POINTSIZE_MIN", 155 },
	{ "D3DRS_POINTSPRITEENABLE", 156 },
	{ "D3DRS_POINTSCALEENABLE", 157 },
	{ "D3DRS_POINTSCALE_A", 158 },
	{ "D3DRS_POINTSCALE_B", 159 },
	{ "D3DRS_POINTSCALE_C", 160 },
	{ "D3DRS_MULTISAMPLEANTIALIAS", 161 },
	{ "D3DRS_MULTISAMPLEMASK", 162 },
	{ "D3DRS_PATCHEDGESTYLE", 163 },
	{ "D3DRS_DEBUGMONITORTOKEN", 165 },
	{ "D3DRS_POINTSIZE_MAX", 166 },
	{ "D3DRS_INDEXEDVERTEXBLENDENABLE", 167 },
	{ "D3DRS_COLORWRITEENABLE", 168 },
	{ "D3DRS_TWEENFACTOR", 170 },
	{ "D3DRS_BLENDOP", 171 },
	{ "D3DRS_POSITIONDEGREE", 172 },
	{ "D3DRS_NORMALDEGREE", 173 },
	{ "D3DRS_SCISSORTESTENABLE", 174 },
	{ "D3DRS_SLOPESCALEDEPTHBIAS", 175 },
	{ "D3DRS_ANTIALIASEDLINEENABLE", 176 },
	{ "D3DRS_MINTESSELLATIONLEVEL", 178 },
	{ "D3DRS_MAXTESSELLATIONLEVEL", 179 },
	{ "D3DRS_ADAPTIVETESS_X", 180 },
	{ "D3DRS_ADAPTIVETESS_Y", 181 },
	{ "D3DRS_ADAPTIVETESS_Z", 182 },
	{ "D3DRS_ADAPTIVETESS_W", 183 },
	{ "D3DRS_ENABLEADAPTIVETESSELLATION", 184 },
	{ "D3DRS_TWOSIDEDSTENCILMODE", 185 },
	{ "D3DRS_CCW_STENCILFAIL", 186 },
	{ "D3DRS_CCW_STENCILZFAIL", 187 },
	{ "D3DRS_CCW_STENCILPASS", 188 },
	{ "D3DRS_CCW_STENCILFUNC", 189 },
	{ "D3DRS_COLORWRITEENABLE1", 190 },
	{ "D3DRS_COLORWRITEENABLE2", 191 },
	{ "D3DRS_COLORWRITEENABLE3", 192 },
	{ "D3DRS_BLENDFACTOR", 193 },
	{ "D3DRS_SRGBWRITEENABLE", 194 },
	{ "D3DRS_DEPTHBIAS", 195 },
	{ "D3DRS_WRAP8", 198 },
	{ "D3DRS_WRAP9", 199 },
	{ "D3DRS_WRAP10", 200 },
	{ "D3DRS_WRAP11", 201 },
	{ "D3DRS_WRAP12", 202 },
	{ "D3DRS_WRAP13", 203 },
	{ "D3DRS_WRAP14", 204 },
	{ "D3DRS_WRAP15", 205 },
	{ "D3DRS_SEPARATEALPHABLENDENABLE", 206 },
	{ "D3DRS_SRCBLENDALPHA", 207 },
	{ "D3DRS_DESTBLENDALPHA", 208 },
	{ "D3DRS_BLENDOPALPHA", 209 },
	{ "D3DRS_FORCE_DWORD", 0x7fffffff },
	{ "D3DZB_FALSE", 0 },
	{ "D3DZB_TRUE", 1 },
	{ "D3DZB_USEW", 2 },
	{ "D3DZB_FORCE_DWORD", 0x7fffffff },
	{ "D3DFILL_POINT", 1 },
	{ "D3DFILL_WIREFRAME", 2 },
	{ "D3DFILL_SOLID", 3 },
	{ "D3DFILL_FORCE_DWORD", 0x7fffffff },
	{ "D3DSHADE_FLAT", 1 },
	{ "D3DSHADE_GOURAUD", 2 },
	{ "D3DSHADE_PHONG", 3 },
	{ "D3DSHADE_FORCE_DWORD", 0x7fffffff },
	{ "D3DBLEND_ZERO", 1 },
	{ "D3DBLEND_ONE", 2 },
	{ "D3DBLEND_SRCCOLOR", 3 },
	{ "D3DBLEND_INVSRCCOLOR", 4 },
	{ "D3DBLEND_SRCALPHA", 5 },
	{ "D3DBLEND_INVSRCALPHA", 6 },
	{ "D3DBLEND_DESTALPHA", 7 },
	{ "D3DBLEND_INVDESTALPHA", 8 },
	{ "D3DBLEND_DESTCOLOR", 9 },
	{ "D3DBLEND_INVDESTCOLOR", 10 },
	{ "D3DBLEND_SRCALPHASAT", 11 },
	{ "D3DBLEND_BOTHSRCALPHA", 12 },
	{ "D3DBLEND_BOTHINVSRCALPHA", 13 },
	{ "D3DBLEND_BLENDFACTOR", 14 },
	{ "D3DBLEND_INVBLENDFACTOR", 15 },
	{ "D3DBLEND_SRCCOLOR2", 16 },
	{ "D3DBLEND_INVSRCCOLOR2", 17 },
	{ "D3DBLEND_FORCE_DWORD", 0x7fffffff },
	{ "D3DCULL_NONE", 1 },
	{ "D3DCULL_CW", 2 },
	{ "D3DCULL_CCW", 3 },
	{ "D3DCULL_FORCE_DWORD", 0x7fffffff },
	{ "D3DCMP_NEVER", 1 },
	{ "D3DCMP_LESS", 2 },
	{ "D3DCMP_EQUAL", 3 },
	{ "D3DCMP_LESSEQUAL", 4 },
	{ "D3DCMP_GREATER", 5 },
	{ "D3DCMP_NOTEQUAL", 6 },
	{ "D3DCMP_GREATEREQUAL", 7 },
	{ "D3DCMP_ALWAYS", 8 },
	{ "D3DCMP_FORCE_DWORD", 0x7fffffff },
	{ "D3DFOG_NONE", 0 },
	{ "D3DFOG_EXP", 1 },
	{ "D3DFOG_EXP2", 2 },
	{ "D3DFOG_LINEAR", 3 },
	{ "D3DFOG_FORCE_DWORD", 0x7fffffff },
	{ "D3DSTENCILOP_KEEP", 1 },
	{ "D3DSTENCILOP_ZERO", 2 },
	{ "D3DSTENCILOP_REPLACE", 3 },
	{ "D3DSTENCILOP_INCRSAT", 4 },
	{ "D3DSTENCILOP_DECRSAT", 5 },
	{ "D3DSTENCILOP_INVERT", 6 },
	{ "D3DSTENCILOP_INCR", 7 },
	{ "D3DSTENCILOP_DECR", 8 },
	{ "D3DSTENCILOP_FORCE_DWORD", 0x7fffffff },
	{ "D3DMCS_MATERIAL", 0 },
	{ "D3DMCS_COLOR1", 1 },
	{ "D3DMCS_COLOR2", 2 },
	{ "D3DMCS_FORCE_DWORD", 0x7fffffff },
	{ "D3DVBF_DISABLE", 0 },
	{ "D3DVBF_1WEIGHTS", 1 },
	{ "D3DVBF_2WEIGHTS", 2 },
	{ "D3DVBF_3WEIGHTS", 3 },
	{ "D3DVBF_TWEENING", 255 },
	{ "D3DVBF_0WEIGHTS", 256 },
	{ "D3DPATCHEDGE_DISCRETE", 0 },
	{ "D3DPATCHEDGE_CONTINUOUS", 1 },
	{ "D3DPATCHEDGE_FORCE_DWORD", 0x7fffffff },
	{ "D3DDMT_ENABLE", 0 },
	{ "D3DDMT_DISABLE", 1 },
	{ "D3DDMT_FORCE_DWORD", 0x7fffffff },
	{ "D3DDEGREE_LINEAR", 1 },
	{ "D3DDEGREE_QUADRATIC", 2 },
	{ "D3DDEGREE_CUBIC", 3 },
	{ "D3DDEGREE_QUINTIC", 5 },
	{ "D3DCULL_FORCE_DWORD", 0x7fffffff },
	{ "D3DBLENDOP_ADD", 1 },
	{ "D3DBLENDOP_SUBTRACT", 2 },
	{ "D3DBLENDOP_REVSUBTRACT", 3 },
	{ "D3DBLENDOP_MIN", 4 },
	{ "D3DBLENDOP_MAX", 5 },
	{ "D3DBLENDOP_FORCE_DWORD", 0x7fffffff },
	{ "D3DSAMP_ADDRESSU", 1 },
	{ "D3DSAMP_ADDRESSV", 2 },
	{ "D3DSAMP_ADDRESSW", 3 },
	{ "D3DSAMP_BORDERCOLOR", 4 },
	{ "D3DSAMP_MAGFILTER", 5 },
	{ "D3DSAMP_MINFILTER", 6 },
	{ "D3DSAMP_MIPFILTER", 7 },
	{ "D3DSAMP_MIPMAPLODBIAS", 8 },
	{ "D3DSAMP_MAXMIPLEVEL", 9 },
	{ "D3DSAMP_MAXANISOTROPY", 10 },
	{ "D3DSAMP_SRGBTEXTURE", 11 },
	{ "D3DSAMP_ELEMENTINDEX", 12 },
	{ "D3DSAMP_DMAPOFFSET", 13 },
	{ "D3DSAMP_FORCE_DWORD", 0x7fffffff },
	{ "D3DTADDRESS_WRAP", 1 },
	{ "D3DTADDRESS_MIRROR", 2 },
	{ "D3DTADDRESS_CLAMP", 3 },
	{ "D3DTADDRESS_BORDER", 4 },
	{ "D3DTADDRESS_MIRRORONCE", 5 },
	{ "D3DTADDRESS_FORCE_DWORD", 0x7fffffff },
	{ "D3DTEXF_NONE", 0 },
	{ "D3DTEXF_POINT", 1 },
	{ "D3DTEXF_LINEAR", 2 },
	{ "D3DTEXF_ANISOTROPIC", 3 },
	{ "D3DTEXF_PYRAMIDALQUAD", 6 },
	{ "D3DTEXF_GAUSSIANQUAD", 7 },
	{ "D3DTEXF_CONVOLUTIONMONO", 8 },
	{ "D3DTEXF_FORCE_DWORD", 0x7fffffff },
	{ "D3DTSS_COLOROP", 1 },
	{ "D3DTSS_COLORARG1", 2 },
	{ "D3DTSS_COLORARG2", 3 },
	{ "D3DTSS_ALPHAOP", 4 },
	{ "D3DTSS_ALPHAARG1", 5 },
	{ "D3DTSS_ALPHAARG2", 6 },
	{ "D3DTSS_BUMPENVMAT00", 7 },
	{ "D3DTSS_BUMPENVMAT01", 8 },
	{ "D3DTSS_BUMPENVMAT10", 9 },
	{ "D3DTSS_BUMPENVMAT11", 10 },
	{ "D3DTSS_TEXCOORDINDEX", 11 },
	{ "D3DTSS_BUMPENVLSCALE", 22 },
	{ "D3DTSS_BUMPENVLOFFSET", 23 },
	{ "D3DTSS_TEXTURETRANSFORMFLAGS", 24 },
	{ "D3DTSS_COLORARG0", 26 },
	{ "D3DTSS_ALPHAARG0", 27 },
	{ "D3DTSS_RESULTARG", 28 },
	{ "D3DTSS_CONSTANT", 32 },
	{ "D3DTSS_FORCE_DWORD", 0x7fffffff },
	{ "D3DTOP_DISABLE", 1 },
	{ "D3DTOP_SELECTARG1", 2 },
	{ "D3DTOP_SELECTARG2", 3 },
	{ "D3DTOP_MODULATE", 4 },
	{ "D3DTOP_MODULATE2X", 5 },
	{ "D3DTOP_MODULATE4X", 6 },
	{ "D3DTOP_ADD", 7 },
	{ "D3DTOP_ADDSIGNED", 8 },
	{ "D3DTOP_ADDSIGNED2X", 9 },
	{ "D3DTOP_SUBTRACT", 10 },
	{ "D3DTOP_ADDSMOOTH", 11 },
	{ "D3DTOP_BLENDDIFFUSEALPHA", 12 },
	{ "D3DTOP_BLENDTEXTUREALPHA", 13 },
	{ "D3DTOP_BLENDFACTORALPHA", 14 },
	{ "D3DTOP_BLENDTEXTUREALPHAPM", 15 },
	{ "D3DTOP_BLENDCURRENTALPHA", 16 },
	{ "D3DTOP_PREMODULATE", 17 },
	{ "D3DTOP_MODULATEALPHA_ADDCOLOR", 18 },
	{ "D3DTOP_MODULATECOLOR_ADDALPHA", 19 },
	{ "D3DTOP_MODULATEINVALPHA_ADDCOLOR", 20 },
	{ "D3DTOP_MODULATEINVCOLOR_ADDALPHA", 21 },
	{ "D3DTOP_BUMPENVMAP", 22 },
	{ "D3DTOP_BUMPENVMAPLUMINANCE", 23 },
	{ "D3DTOP_DOTPRODUCT3", 24 },
	{ "D3DTOP_MULTIPLYADD", 25 },
	{ "D3DTOP_LERP", 26 },
	{ "D3DTOP_FORCE_DWORD", 0x7fffffff },
	{ "D3DPT_POINTLIST", 1 },
	{ "D3DPT_LINELIST", 2 },
	{ "D3DPT_LINESTRIP", 3 },
	{ "D3DPT_TRIANGLELIST", 4 },
	{ "D3DPT_TRIANGLESTRIP", 5 },
	{ "D3DPT_TRIANGLEFAN", 6 },
	{ "D3DPT_FORCE_DWORD", 0x7fffffff }
};