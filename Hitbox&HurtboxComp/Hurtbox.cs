using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hurtbox : MonoBehaviour
{
    public bool isGizmosEnabled = true;
    public Color hurtboxColor = Color.yellow;
    public Collider collider;
    private ColliderState _state = ColliderState.Open;

    public float healthDebug = 10;
    public void GetHitBy(float damage) {
        if (_state == ColliderState.Closed) { return; }
        
        healthDebug -= damage;
        StopCheckingCollision();
    }

     public void StartCheckingCollision(){
        _state = ColliderState.Open;
    }

    public void StopCheckingCollision(){
        _state = ColliderState.Closed;
    }
    private void OnDrawGizmos() {
        if (!isGizmosEnabled){
            return;
        }
        Gizmos.color = hurtboxColor;
        Gizmos.DrawCube(collider.bounds.center, new Vector3(collider.bounds.extents.x * 2, collider.bounds.extents.y * 2, collider.bounds.extents.z * 2)); 

    }
}
