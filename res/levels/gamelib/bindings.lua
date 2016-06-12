ffi = require('ffi')

local bindings = {}
function bindings.bind()
  ffi.cdef([[
    typedef struct GameObject GameObject;
    typedef struct GlyphMat GlyphMat;
    typedef struct UIElement UIElement;
    typedef struct Scene Scene;
    typedef struct MsgBox MsgBox;
    typedef struct Level Level;
    typedef struct Netrom Netrom;
    typedef struct {int x; int y;} V2;

    GlyphMat* GlyphMat_new(char**, int h);

    GameObject* GameObject_new(Level* level, GlyphMat** icon, GlyphMat** mask, int nicon);
    void GameObject_gc(GameObject* self);
    void GameObject_setPos(GameObject* self, int x, int y);
    V2 GameObject_getPos(GameObject* self);
    void GameObject_move(GameObject* self, int x, int y);
    void GameObject_setNormalSpeed(GameObject* self, double speed);
    unsigned long long GameObject_getId(GameObject* self);
    int GameObject_isNull(GameObject* self);
    GameObject * Level_getNearGO(Level * self, GameObject * go);
    V2 GameObject_getOrientationX(GameObject* self);
    void GameObject_setFrame(GameObject* self, int index);

    void Level_addGO(Level* self, GameObject* go);
    GameObject * Level_getGOByPos(Level * self, int x, int y);
    void Level_delGO(Level* self, GameObject* go);
    void Level_addUE(Level* self, UIElement* ue);
    V2 Level_getSP(Level * self, int fx, int fy, int tx, int ty);

    V2 Netrom_getMatrixSize(Netrom* self);

    void UIElement_setPos(UIElement* self, int x, int y);
    void UIElement_setSize(UIElement* self, int x, int y);

    Scene* Scene_new(Level* level);
    void Scene_gc(Scene * self);

    MsgBox* MsgBox_new(Level *level);
    void MsgBox_msg(MsgBox* self, char* msg);
    void MsgBox_gc(MsgBox* self);
  ]])
end

return bindings
