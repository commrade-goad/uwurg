#ifndef MESSAGE_H_
#define MESSAGE_H_

enum MessageType { OK, FAILED, CHANGE_WINDOW_S };

struct Message {
    MessageType mMsgT;
    void *mData;
};

#endif // MESSAGE_H_
