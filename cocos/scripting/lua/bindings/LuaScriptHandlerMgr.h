#ifndef __LUA_SCRIPT_HANDLER_MGR_H__
#define __LUA_SCRIPT_HANDLER_MGR_H__


extern "C" {
#include "tolua++.h"
}


#include "CCObject.h"
#include "ccMacros.h"
#include "CCActionInstant.h"
#include <vector>
#include <map>

NS_CC_BEGIN

class ScheduleHandlerDelegate;


typedef std::vector<ScheduleHandlerDelegate*> VecShedule;
typedef std::map<cocos2d::Node*,VecShedule> MapNodeSchedules;

class ScheduleHandlerDelegate:public cocos2d::Object
{
public:
    ScheduleHandlerDelegate():_isUpdateSchedule(false)
    {}
    virtual ~ScheduleHandlerDelegate()
    {}
    
    static ScheduleHandlerDelegate* create();
    
    void scheduleFunc(float elapse);
    
    virtual void update(float elapse);
    
    void setUpdateSchedule(bool isUpdateSchedule){ _isUpdateSchedule = isUpdateSchedule; }
    bool isUpdateSchedule(){ return _isUpdateSchedule; }
private:
    bool _isUpdateSchedule;
};

class LuaCallFunc:public cocos2d::CallFuncN
{
public:
    LuaCallFunc():_functionLua(nullptr)
    {}
    virtual ~LuaCallFunc()
    {}
    
    static LuaCallFunc* create(const std::function<void(void* self,Node*)>& func);
    bool initWithFunction(const std::function<void(void* self,Node*)>& func);
    virtual LuaCallFunc* clone() const;
    virtual void execute() override;
protected:
    /**
     */
    std::function<void(void* self,Node*)> _functionLua;
    
};

class ScriptHandlerMgr
{
public:
    enum class HandlerType: int
    {
        NODE = 0,
        MENU_CLICKED,
        NOTIFICATION,
        CALLFUNC,
        SCHEDULE,
        TOUCHES,
        KEYPAD,
        ACCELEROMETER,
        
        CONTROL_TOUCH_DOWN,
        CONTROL_TOUCH_DRAG_INSIDE,
        CONTROL_TOUCH_DRAG_OUTSIDE,
        CONTROL_TOUCH_DRAG_ENTER,
        CONTROL_TOUCH_DRAG_EXIT,
        CONTROL_TOUCH_UP_INSIDE,
        CONTROL_TOUCH_UP_OUTSIDE,
        CONTROL_TOUCH_UP_CANCEL,
        CONTROL_VALUE_CHANGED,
        
        WEBSOCKET_OPEN,
        WEBSOCKET_MESSAGE,
        WEBSOCKET_CLOSE,
        WEBSOCKET_ERROR,
        
        GL_NODE_DRAW,
        
        SCROLLVIEW_SCROLL,
        SCROLLVIEW_ZOOM,
        
        TABLECELL_TOUCHED,
        TABLECELL_HIGHLIGHT,
        TABLECELL_UNHIGHLIGHT,
        TABLECELL_WILL_RECYCLE,
        TABLECELL_SIZE_FOR_INDEX,
        TABLECELL_AT_INDEX,
        TABLEVIEW_NUMS_OF_CELLS,
        
        XMLHTTPREQUEST_READY_STATE_CHANGE,
        
        ASSETSMANAGER_PROGRESS,
        ASSETSMANAGER_SUCCESS,
        ASSETSMANAGER_ERROR,
        
        EVENT_LISTENER,
        ARMATURE_EVENT,
        
        EVENTLISTENER_ACC,
        EVENTLISTENER_CUSTIOM,
        
        EVENTLISTENER_KEYBOARD_PRESSED,
        EVENTLISTENER_KEYBOARD_RELEASE,
        
        EVENTLISTENER_TOUCH_BEGAN,
        EVENTLISTENER_TOUCH_MOVED,
        EVENTLISTENER_TOUCH_ENDED,
        EVENTLISTENER_TOUCH_CANCELLED,
        
        EVENTLISTENER_MOUSE_DOWN,
        EVENTLISTENER_MOUSE_UP,
        EVENTLISTENER_MOUSE_MOVE,
        EVENTLISTENER_MOUSE_SCROLL,
    };
    
    typedef int Handler;
    typedef std::pair<HandlerType, Handler> HandlerPair;
    typedef std::vector<HandlerPair> VecHandlerPairs;
    typedef std::map<void*,VecHandlerPairs> MapObjectHandlers;
    
    ScriptHandlerMgr(void);
    virtual ~ScriptHandlerMgr(void);
    static ScriptHandlerMgr* getInstance(void);
        
    void addObjectHandler(void* object,int handler,ScriptHandlerMgr::HandlerType handlerType);
    void removeObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType);
    int  getObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType);
    void removeObjectAllHandlers(void* object);
    
private:
    void init(void);
    static ScriptHandlerMgr* _scriptHandlerMgr;
    MapObjectHandlers _mapObjectHandlers;
};

NS_CC_END

TOLUA_API int tolua_script_handler_mgr_open(lua_State* tolua_S);

#endif //__LUA_SCRIPT_HANDLER_MGR_H__