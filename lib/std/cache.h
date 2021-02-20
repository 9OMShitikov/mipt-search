#pragma once

#include <utility>

template <typename Key, typename Value>
class ICache {
   public:
	virtual Value *Get(const Key &key) = 0;
	virtual bool Put(const Key &key, Value value) = 0;
};

template <typename Key, typename Value>
class LRUCache : public ICache<Key, Value> {
   public:
	explicit LRUCache(int cache_size);

	virtual Value *Get(const Key &key);
	virtual bool Put(const Key &key, Value value);
};
