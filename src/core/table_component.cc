/**
 * Created by Rishi Patel on 11/15/2020.
 */

#include "core/table_component.h"
#include "cinder/gl/gl.h"

namespace snooker {

TableComponent::TableComponent(const glm::vec2& position)
    : position_(position) {}

StraightEdge::StraightEdge(const glm::vec2& position)
    : TableComponent(position) {}

}  // namespace snooker