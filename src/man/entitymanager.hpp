//#pragma once
//#include <cstdint>
//#include <vector>
//
//namespace ECS{
//	
//	struct Entity_t{
//		//entity con sprite
//		explicit Entity_t(uint32_t _w, uint32_t _h) : w(_w), h(_h) {
//			sprite.reserve(w*h);
//		}
//		uint32_t x {0}, y {0};
//		uint32_t w {0}, h {0};
//		std::vector<uint32_t> sprite {};
//	};
//
//	struct EntityManager_t{
//		using VecEntities_t = std::vector<Entity_t>;
//
//		static constexpr std::size_t kNUMINITIALENTITIES {1000};
//
//		explicit EntityManager_t();
//
//		void createEntity(uint32_t w, uint32_t h, uint32_t color);
//
//		const VecEntities_t& getEntities() const { return m_Entity; };
//
//	private:
//		//No por punteros te comes la cache
//		VecEntities_t m_Entity {};
//	};
//
//} //END