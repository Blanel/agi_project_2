namespace revel
{
	class TerrainManager
	{
		int optimalChunks;
	public:
		TerrainManager(int optimalChunks);
		~TerrainManager();
		void prune();
		void generate();
	};
}