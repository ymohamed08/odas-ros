    
    #include "scan.h"

    // +----------------------------------------------------------+
    // | Constructor                                              |
    // +----------------------------------------------------------+

    scans_obj * scans_construct_null(const unsigned int nLevels) {

        scans_obj * obj;

        obj = (scans_obj *) malloc(sizeof(scans_obj));

        obj->nLevels = nLevels;
        
        obj->points = (points_obj **) malloc(sizeof(points_obj *) * nLevels);
        memset(obj->points, 0x00, sizeof(points_obj *) * nLevels);

        obj->tdoas = (tdoas_obj **) malloc(sizeof(tdoas_obj *) * nLevels);
        memset(obj->tdoas, 0x00, sizeof(tdoas_obj *) * nLevels);

        obj->deltas = (deltas_obj **) malloc(sizeof(deltas_obj *) * nLevels);
        memset(obj->deltas, 0x00, sizeof(deltas_obj *) * nLevels);

        obj->spatialindexes = (spatialindexes_obj **) malloc(sizeof(spatialindexes_obj *) * nLevels);
        memset(obj->spatialindexes, 0x00, sizeof(spatialindexes_obj *) * nLevels);

        obj->pairs = (pairs_obj *) NULL;

        obj->indexes = (indexes_obj **) malloc(sizeof(indexes_obj *) * nLevels);
        memset(obj->indexes, 0x00, sizeof(indexes_obj *) * nLevels);

        return obj;

    }

    // +----------------------------------------------------------+
    // | Destructor                                               |
    // +----------------------------------------------------------+

    void scans_destroy(scans_obj * obj) {

        unsigned int iLevel;

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {

            if (obj->points[iLevel] != NULL) {
                points_destroy(obj->points[iLevel]);
            }

            if (obj->tdoas[iLevel] != NULL) {
                tdoas_destroy(obj->tdoas[iLevel]);
            }

            if (obj->deltas[iLevel] != NULL) {
                deltas_destroy(obj->deltas[iLevel]);
            }

            if (obj->spatialindexes[iLevel] != NULL) {
                spatialindexes_destroy(obj->spatialindexes[iLevel]);
            }

            if (obj->indexes[iLevel] != NULL) {
                indexes_destroy(obj->indexes[iLevel]);
            }            

        }

        if (obj->pairs != NULL) {
            pairs_destroy(obj->pairs);
        }

        free((void *) obj->points);
        free((void *) obj->tdoas);
        free((void *) obj->deltas);
        free((void *) obj->spatialindexes);
        free((void *) obj->indexes);

        free((void *) obj);

    }
