#include <cassert>
#include "trie.hpp"

#ifdef assert
//We undefined this macro to not shadow our implementation of assert.
#undef assert
#endif

/**
 * @brief Check an assertion.
 * In Debug mode, if the assertion is not met, a segfault is generated.
 * @param assertion
 */
inline void assert(bool assertion)
{
#ifndef NDEBUG
    (void)((assertion) || (__assert ("Assert violation!", __FILE__, __LINE__),0));
#endif
}


TrieNode::TrieNode ()
{
    //TODO
    //Hint: Do you need to do something?
};

TrieNode::Ref TrieNode::create()
{
    return std::make_shared<TrieNode>();
}

bool
TrieNode::has(char k) const
{
    bool ret_v = false;
    //TODO
    if(children_.count(k))
        ret_v = true;
    //
    return ret_v;
}

TrieNode::Ref
TrieNode::child(char k) const
{
    assert(has(k));
    TrieNode::Ref ret_v;
    //TODO
    ret_v = children_.find(k) -> second;
    //
    return ret_v;
}

std::string const&
TrieNode::value() const
{
    return value_;
}

const std::map<char, TrieNode::Ref> &TrieNode::children() const
{
    return children_;
}

void
TrieNode::set_value(std::string const& new_v)
{
    value_ = new_v;
}

void
TrieNode::insert(char k, Ref node)
{
    //TODO
    assert(!has(k));
    children_.emplace(k, node);
    //
}

Trie::Trie()
{
    //TODO
    //Hint: Do you need to do something?
}

Trie::Ref Trie::create()
{
    return std::make_shared<Trie>();
}

TrieNode::Ref Trie::root() const
{
    //TODO
    return root_;
    //
}

bool
Trie::has(std::string const& k) const
{
    bool found = false;
    //TODO
    //Remember: The Trie can have a prefix==k but does not store the key k.
    TrieNode::Ref node = find_node(k);
    if(node != nullptr && node -> value()==k)
        found = true;
    //
    return found;
}

std::vector<std::string>
Trie::keys(std::string const& pref) const
{
    std::vector<std::string> keys;
    //TODO
    TrieNode::Ref node = find_node(pref);
    if(node != nullptr)
        preorder_traversal(node, keys);
    //
    return keys;
}


void
Trie::insert(std::string const& k)
{
    //TODO
    if(root_ == nullptr)
        root_ = TrieNode::create();
    
    TrieNode::Ref node = root_;
    TrieNode::Ref newNode;
    for(unsigned int i = 0; i < k.size(); i++){
        if(node -> has(k[i]))
            node = node -> child(k[i]);
        else{
            newNode = newNode -> create();
            node -> insert(k[i], newNode);
            node = newNode;
        }
    }
    node -> set_value(k);
    //
    assert(has(k));
}

TrieNode::Ref
Trie::find_node(std::string const& pref) const
{
    TrieNode::Ref node;
    //TODO
    unsigned int i = 0;
    node = root_;
    while(i < pref.size() && node != nullptr){
        if(node -> has(pref[i])){
            node = node -> child(pref[i]);
            i++;
        }
        else
            node = nullptr;     
    }
    //
    return node;
}

void
Trie::preorder_traversal(TrieNode::Ref const& node,
                         std::vector<std::string> & keys) const
{
    //TODO
    if (node -> value() != "")
        keys.push_back(node -> value());

    for(std::map<char, std::shared_ptr<TrieNode>>::const_iterator i = node -> children().begin(); i != node -> children().end(); i++)
    {
        preorder_traversal(i->second, keys);
    }
    //
}
