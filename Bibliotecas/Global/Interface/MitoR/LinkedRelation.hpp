//
// Created by Robson on 07/05/2023.
//
#pragma once

#include <QLinkedList>
#include <QVector>
#include <spdlog/fmt/fmt.h>
#include <cassert>

namespace MitoR
{
  template<class T>
  class LinkedRelation
  {
  public:
    using Item = T;
    using Container = QLinkedList<Item>;
    using Iterator = typename Container::iterator;
    using ConstIterator = typename Container::const_iterator;
    struct Relation {
      using List = QVector<ConstIterator>;
      ConstIterator itItem;
      List pais;
      List filhos;
    };
    using Relacoes = QVector<Relation>;

    LinkedRelation();
    inline Iterator begin() { return container.begin(); }
    inline ConstIterator cbegin() { return container.cbegin(); }
    inline Iterator end() { return container.end(); }
    inline ConstIterator cend() { return container.cend(); }

    inline bool is_empty() { return container.isEmpty(); }

    Iterator insert(Item item);
    Iterator insert(ConstIterator itAntes, Item item);
    Iterator insert(Item item, ConstIterator itItemPai);
    Iterator insert(ConstIterator itAntes, Item item, ConstIterator itItemPai);
    bool associate(ConstIterator itItem, ConstIterator itItemPai);
    bool remove(ConstIterator itItem);
    void clear();

    ConstIterator invisibleRootItem();
    QVector<ConstIterator> list_parents(ConstIterator itItem) const;
    QVector<ConstIterator> list_children(ConstIterator itItem) const;

    std::string debug(std::string (*fnPredToString)(ConstIterator it, ConstIterator end));

  protected:
    typename Relacoes::iterator search_relation(ConstIterator it)
    {
      return std::find_if(relacoes.begin(), relacoes.end(), [it](const Relation &rel) { return rel.itItem == it; });
    }
    typename Relacoes::const_iterator search_relation(ConstIterator it) const
    {
      return std::find_if(relacoes.begin(), relacoes.end(), [it](const Relation &rel) { return rel.itItem == it; });
    }

  private:
    Container container;
    Relacoes relacoes;
  };

  template<class T>
  inline LinkedRelation<T>::LinkedRelation()
  {
    relacoes.insert(relacoes.end(), {container.end(), {}, {}});
  }
  template<class T>
  typename LinkedRelation<T>::Iterator LinkedRelation<T>::insert(Item item)
  {
    auto it = container.insert(container.end(), item);
    if (it != container.end()) {
      relacoes.insert(relacoes.end(), {it, {}, {}});
      return it;
    }
    return container.end();
  }
  template<class T>
  typename LinkedRelation<T>::Iterator LinkedRelation<T>::insert(LinkedRelation::ConstIterator itAntes, Item item)
  {
    auto it = container.insert(itAntes, item);
    if (it != container.end()) {
      relacoes.insert(relacoes.end(), {it, {}, {}});
      return it;
    }
    return container.end();
  }
  template<class T>
  typename LinkedRelation<T>::Iterator LinkedRelation<T>::insert(Item item, LinkedRelation::ConstIterator itItemPai)
  {
    auto itItem = container.insert(container.end(), item);
    if (itItem != container.end()) {
      relacoes.insert(relacoes.end(), {itItem, {}, {}});
      if(associate(itItem, itItemPai))
        return itItem;
    }
    return container.end();
  }
  template<class T>
  typename LinkedRelation<T>::Iterator LinkedRelation<T>::insert(LinkedRelation::ConstIterator itAntes, Item item, LinkedRelation::ConstIterator itItemPai)
  {
    auto itItem = container.insert(itAntes, item);
    if (itItem != container.end()) {
      relacoes.insert(relacoes.end(), {itItem, {}, {}});
      if(associate(itItem, itItemPai))
        return itItem;
    }
    return container.end();
  }
  template<class T>
  bool LinkedRelation<T>::associate(ConstIterator itItem, ConstIterator itItemPai)
  {
    if (itItem == itItemPai) {
      return false;
    }

    auto itRelItem = search_relation(itItem);
    assert(itRelItem != relacoes.end());
    if (!itRelItem->pais.contains(itItemPai)) {
      itRelItem->pais.push_back(itItemPai);
    }
    auto itRelItemPai = search_relation(itItemPai);
    assert(itRelItem != relacoes.end());
    if (!itRelItemPai->filhos.contains(itItem)) {
      itRelItemPai->filhos.push_back(itItem);
    }

    return true;
  }
  template<class T>
  bool LinkedRelation<T>::remove(ConstIterator itItem)
  {
    auto itRelItem = search_relation(itItem);
    for (auto itItemPai: itRelItem->pais) {
      auto itRelItemPai = search_relation(itItemPai);
      itRelItemPai->filhos.removeOne(itItem);
    }
    for (auto itItemFilho: itRelItem->filhos) {
      auto listaPais = list_parents(itItemFilho);
      if(listaPais.size() < 2)
        remove(itItemFilho);
      else {
        auto itRelItemFilho = search_relation(itItemFilho);
        itRelItemFilho->pais.removeOne(itItem);
      }
    }
    if (itRelItem->itItem != this->container.end()) {
      this->relacoes.erase(itRelItem);
      this->container.erase(itItem);
      return true;
    }

    return false;
  }
  template<class T>
  void LinkedRelation<T>::clear()
  {
    container.clear();
    relacoes.clear();
    relacoes.insert(relacoes.end(), {container.end(), {}, {}});
  }
  template<class T>
  std::string LinkedRelation<T>::debug(std::string (*fnToStdString)(ConstIterator it, ConstIterator end))
  {
    std::string buf;
    for (auto it = begin(); it != end(); it++) {
      auto item = fnToStdString(it, end());
      std::string pais;
      auto rel = search_relation(it);
      if (rel != relacoes.end()) {
        for (auto itPai = rel->pais.begin(); itPai != rel->pais.end(); itPai++) {
          if(*itPai != cend()) {
            pais += fnToStdString(*itPai, end());
            pais += ", ";
          }
        }
      }
      std::string filhos;
      if (rel != relacoes.end()) {
        for (auto itFilho = rel->filhos.begin(); itFilho != rel->filhos.end(); itFilho++) {
          if(*itFilho != cend()) {
            filhos += fnToStdString(*itFilho, end());
            filhos += ", ";
          }
        }
      }
      buf += fmt::format("[{} : [{}] [{}] ]\n", item, pais, filhos);
    }
    return buf;
  }
  template<class T>
  QVector<typename LinkedRelation<T>::ConstIterator> LinkedRelation<T>::list_parents(LinkedRelation<T>::ConstIterator itItem) const
  {
    auto itRelItem = search_relation(itItem);
    if(itRelItem != relacoes.end()) {
      auto vec = itRelItem->pais;
      vec.removeOne(container.end());
      return vec;
    }
    return {};
  }
  template<class T>
  QVector<typename LinkedRelation<T>::ConstIterator> LinkedRelation<T>::list_children(LinkedRelation::ConstIterator itItem) const
  {
    auto itRel = search_relation(itItem);
    if(itRel != relacoes.end()) {
      auto vec = itRel->filhos;
      vec.removeOne(container.end());
      return vec;
    }
    return {};
  }
  template<class T>
  typename LinkedRelation<T>::ConstIterator LinkedRelation<T>::invisibleRootItem()
  {
    return end();
  }
}