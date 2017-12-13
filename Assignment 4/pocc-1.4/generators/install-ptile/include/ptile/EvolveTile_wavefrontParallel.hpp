#ifndef PTILE_EVOLVETILE_WAVEFRONT_H
# define PTILE_EVOLVETILE_WAVEFRONT_H

#include <past/past.h>
# include <ptile/GenericUtility.hpp>

class EvolveWavefrontTileGenerator
{

public:

	static s_past_node_t* EvolveTileCodeGenerateForWavefrontParallelLoop (s_past_node_t* pointLoops, s_past_node_t* tileLoops, 
								s_past_node_t* tiledCode, s_ptile_options_t* options);

	static s_past_node_t* AddPrologue (vector<string>* iteratorNames, s_past_node_t* tiledCode, s_ptile_options_t* options);
	static void AddScannedCheckInPointLoops (vector<string>* iteratorNames, s_past_node_t* evolveCode);
	static s_past_node_t* GetParentOfPointLoops (s_past_node_t*  evolveCode);
	static void StoreParentOfPointLoops (s_past_node_t* node, void* data);
	static s_past_if_t* GetFullTileForWFullOnwards (vector<string>* iteratorNames, s_past_node_t* fullTileBody);
	static s_past_node_t* GetPartialTile (vector<string>* iteratorNames, s_past_node_t* body);
	static s_past_node_t* GeneratePointLoopCheck (vector<string>* iteratorNames);
	static s_past_node_t* GeneratePointLoopEnteringCheck (vector<string>* iteratorNames);
	static s_past_node_t* CreateIfNodeWithCheck (s_past_node_t* body, s_past_node_t* condition);
	static void AddCheckBeforeCloogStatement (s_past_node_t* node, void* data);
	static void InsertPointLoopCheckBeforeCloogStatements (s_past_node_t* check, s_past_node_t* body);
	static s_past_node_t* GenerateSwitchCode (vector<string>* iteratorNames, s_past_node_t* tileLoops);
	static  s_past_if_t* GetIfWPTtileFullOnwords (s_past_node_t* fullTileBody);
	static  s_past_node_t* GetIfWPTtileFullOnwordsCondition ();
	static s_past_node_t* GenerateCheckSkippingCondition (vector<string>* iteratorNames);
	static s_past_node_t* GetFullTileInChangeOverRegion (vector<string>* iteratorNames, s_past_node_t* body);
	static bool IsIteratorSuffix_t1(s_past_for_t* node);
}; // class EvolveWavefrontTileGenerator

#endif // PTILE_EVOLVETILE_WAVEFRONT_H
