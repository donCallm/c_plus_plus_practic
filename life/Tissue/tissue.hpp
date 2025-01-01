// #pragma once

// #include <type_traits>
// #include "Cells/cells.hpp"

// constexpr const bool CONNECTED_BY_CYTOPLASM = true;

// template <bool Connected = true, class CellType = Cell>
// using Cell_with_thread =
//     std::pair<std::integral_constant<bool, Connected>,CellType>;

// template <class CellType = Cell>
// using Cells =
//     std::vector<std::unique_ptr<Cell_with_thread<CONNECTED_BY_CYTOPLASM, Cell>>>;

// struct DefaultTissue {

    
// protected:
//     Cells<Cell> _cells;
// };
