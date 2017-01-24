#ifndef __DATA_H__
#define __DATA_H__

#ifndef countof
# define countof(A) (sizeof(A) / sizeof(*(A)))
#endif /* countof */

struct Operation {
  /**< Arrow key states. */
  bool px : 1;
  bool py : 1;
  /**< A/B key states. */
  bool pa : 1;
  bool pb : 1;

  Operation();
};

void load(Operation* o);
void save(Operation* o);

#endif /* __DATA_H__ */
