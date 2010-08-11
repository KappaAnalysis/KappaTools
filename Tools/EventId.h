#include "DataFormats/src/classes.h"

struct EventId{
  EventId():rid(0),lid(0),nCmsEvent(0){}
  EventId(run_id r,lumi_id l,event_id e):rid(r),lid(l),nCmsEvent(e){}
  run_id rid;
  lumi_id lid;
  event_id nCmsEvent;
  bool operator < (const EventId &other) const {
    if (rid<other.rid) return true;
    else if (lid<other.lid) return true;
    else if (nCmsEvent<other.nCmsEvent) return true;
    else return false;
  }
};

std::ostream& operator <<(std::ostream& output, const EventId& id);
