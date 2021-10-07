#include <tuple>
#include <variant>
#include <type_traits>
#include "Application.h"
#include "Panel.h"
#include "SimpleButton.h"

using namespace VertexUI::Hle;

struct Model { int count{ 0 }; };
auto Init() { return Model(); }

struct Increment {};
struct Increment10 {};
using Msg = std::variant<Increment, Increment10>;

class Update
{
public:
    void operator()(Increment const& message, Model& model)
    {
        ++model.count;
    }
    void operator()(Increment10 const& message, Model& model)
    {
        model.count += 10;
    }
};

auto View(Model const& model)
{
    return Hle::Panel {
        L"Hello",
        (new SimpleButton())->SetText(L"µ÷Ï·Ë®Ë®")->SetRect({
            .left = -40,
            .top = -40,
            .right = 140,
            .bottom = 40
        })
    };
}

int Main(int, wchar_t**)
{
    Application<Update, Model> app(Init, View);
    app.RunMessageLoop();
    return 0;
}