/* Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   51 Franklin Street, Suite 500, Boston, MA 02110-1335 USA */

#ifndef OBSERVER_TRANS
#define OBSERVER_TRANS

#include "gcs_plugin.h"
#include "my_stacktrace.h"
#include "gcs_communication_interface.h"
#include "gcs_binding_factory.h"

/*
  Transaction lifecycle events observers.
*/
int gcs_trans_before_commit(Trans_param *param);

int gcs_trans_before_rollback(Trans_param *param);

int gcs_trans_after_commit(Trans_param *param);

int gcs_trans_after_rollback(Trans_param *param);

extern Trans_observer trans_observer;

/*
  @class Transaction_Message
  Class to convey the serialized contents of the TCLE
 */
class Transaction_Message: public Gcs_plugin_message
{
public:
  /**
   Default constructor
   */
  Transaction_Message();
  virtual ~Transaction_Message();

  /**
    Appends IO_CACHE data to the internal buffer

    @param[in] src the IO_CACHE to copy data from

    @return true in case of error
   */
  bool append_cache(IO_CACHE *src);

protected:
  /*
   Implementation of the template methods
   */
  void encode_message(vector<uchar>* buf);
  void decode_message(uchar* buf, size_t len);

private:
  vector<uchar> data;
};

/**
  Broadcasts the Transaction Message

  @param msg the message to broadcast

  @return true in case of error
 */
bool send_transaction_message(Transaction_Message* msg);

#endif /* OBSERVER_TRANS */
